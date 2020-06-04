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
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "../../../../public/bt/ecs/event/IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include ecs::IEventListener
#ifndef ECS_I_EVENT_LISTENER_HXX
#include "../../../../public/bt/ecs/event/IEventListener.hxx"
#endif // !ECS_I_EVENT_LISTENER_HXX

// DEBUG
#if defined( DEBUG )

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
// ecs::EventsManager
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    ecs_sptr<EventsManager> EventsManager::mInstance(nullptr);

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    EventsManager::EventsManager()
            : mIDStorage(),
              mEventsByThread(),
              mEventListeners()
    {
    }

    EventsManager::~EventsManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_sptr<EventsManager> EventsManager::getInstance()
    { return mInstance; }

    EventsManager::events_deque& EventsManager::getEventsQueue( const unsigned char pThread )
    { return mEventsByThread[pThread]; }

    // ===========================================================
    // METHODS
    // ===========================================================

    void EventsManager::handleEvent( ecs_sptr<ecs_IEvent>& pEvent, const ecs_uint8_t pThread )
    {
        event_listeners_list& listeners = mEventListeners[pEvent->getTypeID()];

        event_listener eventListener;
        const ecs_size_t listenersCount = listeners.Count();

        for( ecs_size_t i = 0; i < listenersCount; i++ )
        {
            if ( listeners.Count() < listenersCount )
                break;

            eventListener = listeners[i];

            try
            {
                if ( eventListener->OnEvent( pEvent, pThread ) )
                    return;
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) // DEBUG
                ecs_String logMsg = u8"EventsManager::handleEvent: ERROR ";
                logMsg += pException.what();
                ecs_log::Print( logMsg.c_str(), ecs_log_level::Error );
#endif // DEBUG
                return;
            }
        }
    }

    void EventsManager::Subscribe( const ecs_TypeID eventType, ecs_sptr<ecs_IEventListener> pListener )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        event_listeners_list& listeners = instance->mEventListeners[eventType];

#if defined( DEBUG ) // DEBUG
        ecs_assert( !listeners.Find(pListener, nullptr) && "EventsManager::subListener - already stored." );
#endif // DEBUG

        listeners.Push( pListener );
    }

    void EventsManager::Unsubscribe( const ecs_TypeID eventType, ecs_sptr<ecs_IEventListener>& pListener )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        event_listeners_list& listeners = instance->mEventListeners[eventType];

        listeners.Erase( pListener, true );
    }

    void EventsManager::sendEvent( ecs_sptr<ecs_IEvent> pEvent, const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        instance->handleEvent( pEvent, pThread );
    }

    void EventsManager::queueEvent( ecs_sptr<ecs_IEvent> pEvent, const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        events_deque& eventsQueue = instance->mEventsByThread[pThread];
        eventsQueue.PushBack( pEvent );
    }

    void EventsManager::Update( const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        events_deque& eventsDeque = instance->mEventsByThread[pThread];

        event_t event = eventsDeque.Front();
        while( event != nullptr )
        { instance->handleEvent( event, pThread ); }
    }

    ecs_ObjectID EventsManager::generateEventID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<EventsManager> instance = getInstance();
        return instance != nullptr ? instance->mIDStorage.getAvailableID(pType) : ECS_INVALID_OBJECT_ID;
    }

    void EventsManager::releaseEventID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<EventsManager> instance = getInstance();

        if ( instance != nullptr )
            instance->mIDStorage.releaseID(pType, pID);
    }

    ECS_API void EventsManager::Initialize()
    {
        if ( mInstance != nullptr )
            return;

        mInstance = ecs_new<EventsManager>();
    }

    ECS_API void EventsManager::Terminate()
    {
        mInstance = nullptr;
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
