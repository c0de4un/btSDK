/**
* Copyright © 2020 Denis Z. (code4un@yandex.ru) All rights reserved.
* Authors: Denis Z. (code4un@yandex.ru)
* All rights reserved.
* Language: C++
* License: see LICENSE.txt
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must display the names 'Denis Zyamaev' and
* in the credits of the application, if such credits exist.
* The authors of this work must be notified via email (code4un@yandex.ru) in
* this case of redistribution.
* 3. Neither the name of copyright holders nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
* IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**/

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef ECS_SYSTEM_HPP
#include "../../../../public/bt/ecs/system/System.hpp"
#endif // !ECS_SYSTEM_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "../../../public/bt/ecs/event/IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include ecs::EventsManager
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include ecs::assert
#ifndef ECS_ASSERT_HPP
#include "../../../../public/bt/ecs/types/ecs_assert.hpp"
#endif // !ECS_ASSERT_HPP

// Include ecs::log
#ifndef ECS_LOG_HPP
#include "../../../../public/bt/ecs/types/ecs_log.hpp"
#endif // !ECS_LOG_HPP

// Include ecs::string
#ifndef ECS_STRING_HPP
#include "../../../../public/bt/ecs/types/ecs_string.hpp"
#endif // !ECS_STRING_HPP

#endif
// DEBUG

// ===========================================================
// ecs::System
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    System::System(const ecs_TypeID pType )
        : mStateMutex(),
        mCurrentState(SYSTEM_STATE_NOT_STARTED),
        mTypeID( pType ),
        mID( ecs_Systems::generateSystemID(pType) )
    {
    }

    System::~System()
    {
        ecs_Systems::releaseSystemID( mTypeID, mID );
    }

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    unsigned char System::getState() const
    {
        ecs_SpinLock stateLock( &mStateMutex );
        const unsigned char state = mCurrentState;
        return state;
    }

    bool System::setState(const unsigned char newState)
    {
        ecs_SpinLock stateLock(&mStateMutex);
        if (newState == mCurrentState)
            return false;

        mCurrentState = newState;
        return true;
    }

    ecs_TypeID System::getTypeID() const BT_NOEXCEPT
    { return mTypeID; }

    ecs_ObjectID System::getID() const BT_NOEXCEPT
    { return mID; }

    bool System::isPaused() const noexcept
    { return mCurrentState > SYSTEM_STATE_STARTED && mCurrentState != SYSTEM_STATE_RESUMING; }

    bool System::isStarted() const noexcept
    { return mCurrentState > SYSTEM_STATE_NOT_STARTED && mCurrentState < SYSTEM_STATE_STOPPED; }

    // ===========================================================
    // METHODS
    // ===========================================================

    ECS_API ecs_sptr<ecs_ISystem> System::That( System* const pInstance )
    { return ecs_Systems::getSystem( pInstance->mTypeID ); }

    ECS_API void System::SubscribeSystem( System* const pInstance, const ecs_vec<ecs_TypeID>& pEvents )
    {
        ecs_sptr<ecs_ISystem> system = That(pInstance);
        ecs_sptr<ecs_IEventListener> listener = ecs_Memory::StaticCast<ecs_IEventListener, ecs_ISystem>( system );
        ecs_Events::SubscribeBatch( pEvents, listener );
    }

    ECS_API void System::UnsubscribeSystem( System* const pInstance, const ecs_vec<ecs_TypeID>& pEvents )
    {
        ecs_sptr<ecs_ISystem> system = That(pInstance);
        ecs_sptr<ecs_IEventListener> listener = ecs_Memory::StaticCast<ecs_IEventListener, ecs_ISystem>( system );
        ecs_Events::UnsubscribeBatch( pEvents, listener );
    }

    bool System::onStart()
    {
        return true;
    }

    bool System::onResume()
    {
        return true;
    }

    void System::onPause()
    {
    }

    void System::onStop()
    {
    }

    // ===========================================================
    // ecs::ISystem
    // ===========================================================

    bool System::Start()
    {
        bool result = false;

        if ( isStarted() )
        {
            result = true;

            if ( isPaused() && setState(SYSTEM_STATE_RESUMING) )
                result = onResume();
        }
        else
        {
            setState(SYSTEM_STATE_STARTING);
            result = onStart();
        }

        setState(SYSTEM_STATE_STARTED);
        return result;
    }

    void System::Pause()
    {
        if ( !isStarted() || !isPaused() || !setState(SYSTEM_STATE_PAUSING) )
            return;

        onPause();

        setState(SYSTEM_STATE_PAUSED);
    }

    void System::Stop()
    {
        if ( !isStarted() || !setState(SYSTEM_STATE_STOPPING) )
            return;

        onStop();

        setState(SYSTEM_STATE_STOPPED);
    }

    // ===========================================================
    // ecs::IEventListener
    // ===========================================================

    char System::OnEvent( ecs_sptr<ecs_IEvent> pEvent, const bool pAsync, const unsigned char pThread )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_String logMsg = u8"System::OnEvent: Event Type=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getTypeID() );
        logMsg += u8"; ID=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getID() );
        logMsg += u8"Thread-Type=";
        logMsg += ecs_StringUtil::toString<unsigned char>( pThread );
        ecs_log::Print(logMsg.c_str(), static_cast<unsigned char>(ecs_log_level::Debug) );
#endif // DEBUG
        return 0;
    }

    void System::onEventError( ecs_sptr<ecs_IEvent> pEvent, const std::exception& pException, const bool pAsync, const unsigned char pThread )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_String logMsg = u8"System::onEventError: ERROR=";
        logMsg += pException.what();
        logMsg += u8"; Event Type=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getTypeID() );
        logMsg += u8"; ID=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getID() );
        logMsg += u8"Thread-Type=";
        logMsg += ecs_StringUtil::toString<unsigned char>( pThread );
        ecs_log::Print(logMsg.c_str(), static_cast<unsigned char>(ecs_log_level::Error) );
#endif // DEBUG
    }

    // ===========================================================
    // ecs::IEventInvoker
    // ===========================================================

    void System::onEventSent( ecs_sptr<ecs_IEvent>& pEvent, const bool pAsync, const ecs_uint8_t pThread )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_String logMsg = u8"System::onEventSent: Event Type=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getTypeID() );
        logMsg += u8"; ID=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getID() );
        logMsg += u8"Thread-Type=";
        logMsg += ecs_StringUtil::toString<unsigned char>( pThread );
        ecs_log::Print(logMsg.c_str(), static_cast<unsigned char>(ecs_log_level::Debug) );
#endif // DEBUG
    }

    void System::onEventSentError( ecs_sptr<ecs_IEvent>& pEvent, const std::exception& pException, const bool pAsync, const ecs_uint8_t pThread )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_String logMsg = u8"System::onEventSentError: ERROR=";
        logMsg += pException.what();
        logMsg += u8"; Event Type=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getTypeID() );
        logMsg += u8"; ID=";
        logMsg += ecs_StringUtil::toString<ecs_TypeID>( pEvent->getID() );
        logMsg += u8"Thread-Type=";
        logMsg += ecs_StringUtil::toString<unsigned char>( pThread );
        ecs_log::Print(logMsg.c_str(), static_cast<unsigned char>(ecs_log_level::Error) );
#endif // DEBUG
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------