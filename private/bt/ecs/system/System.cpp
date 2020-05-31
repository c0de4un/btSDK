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
        mID( ecs_SystemsManager::generateSystemID(pType) )
    {
    }

    System::~System()
    {
        ecs_SystemsManager::releaseSystemID( mTypeID, mID );
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

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------