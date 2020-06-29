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
#ifndef ECS_EVENT_HPP
#include "../../../../public/bt/ecs/event/Event.hpp"
#endif // !ECS_EVENT_HPP

// Include ecs::EventsManager
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// Include ecs::IEventInvoker
#ifndef BT_CORE_I_EVENT_INVOKER_HXX
#include "../../../../public/bt/ecs/event/IEventInvoker.hxx"
#endif // !BT_CORE_I_EVENT_INVOKER_HXX

// ===========================================================
// ecs::Event
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    Event::Event( const ecs_TypeID pType, const bool pRepeat, ecs_wptr<ecs_IEventInvoker> pCaller )
        : mTypeID( pType ),
        mID(ecs_Events::generateEventID(pType) ),
        mInvoker( pCaller ),
        mHandled( false ),
        mRepeatable( pRepeat )
    {
    }

    Event::~Event()
    {
        ecs_Events::releaseEventID(mTypeID, mID );
    }

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_TypeID Event::getTypeID() const ECS_NOEXCEPT
    { return mTypeID; }

    ecs_ObjectID Event::getID() const ECS_NOEXCEPT
    { return mID; }

    bool Event::isHandled() const BT_NOEXCEPT
    { return mHandled; }

    bool Event::isRepeatable() const ECS_NOEXCEPT
    { return mRepeatable; }

    void Event::setRepeat( const bool pRepeat ) ECS_NOEXCEPT
    { mRepeatable = pRepeat; }

    // ===========================================================
    // METHODS
    // ===========================================================

    void Event::onError( ecs_sptr<IEvent>& pEvent, const std::exception& pException, const bool pAsync, const unsigned pThread )
    {
        ecs_sptr<ecs_IEventInvoker> invoker = mInvoker.lock();

        if ( invoker != nullptr )
            invoker->onEventSentError( pEvent, pException, pAsync, pThread );
    }

    void Event::onSend( ecs_sptr<IEvent>& pEvent, const bool pAsync, const unsigned pThread )
    {
        ecs_sptr<ecs_IEventInvoker> invoker = mInvoker.lock();

        if ( invoker != nullptr )
            invoker->onEventSent( pEvent, pAsync, pThread );
    }

    ECS_API char Event::Send( ecs_sptr<IEvent>& pEvent, const bool pAsync, const ecs_uint8_t pThread )
    {
        char result = 0;

        // Send.
        if ( !pAsync )
            result = ecs_Events::sendEvent(pEvent, pThread );
        else
            ecs_Events::queueEvent(pEvent, pThread );

        return result;
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------