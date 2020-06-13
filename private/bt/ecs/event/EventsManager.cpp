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
            : mEnabled(true),
              mIDStorage(),
              mIDMutex(),
              mEventsByThread(),
              mEventsMutex(),
              mEventListeners(),
              mEventListenersMutex()
    {
    }

    EventsManager::~EventsManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_sptr<EventsManager> EventsManager::getInstance()
    { return mInstance; }

    EventsManager::events_queues_storage& EventsManager::getEventsQueue( const unsigned char pThread )
    {
        ecs_SpinLock lock( &mEventsMutex );
        return mEventsByThread[pThread];
    }

    EventsManager::event_listeners_storage& EventsManager::getEventListeners( const ecs_TypeID pType )
    {
        ecs_SpinLock lock( &mEventListenersMutex );
        return mEventListeners[pType];
    }

    ECS_API EventsManager::event_ptr EventsManager::getNextEvent( events_queues_storage& eventsStorage )
    {
        ecs_SpinLock  lock( &eventsStorage.mMutex );

        if ( !eventsStorage.mItem.empty() )
        {
            event_ptr result = eventsStorage.mItem.front();
            eventsStorage.mItem.pop_front();
            return result;
        }

        return event_ptr( nullptr );
    }

    ECS_API EventsManager::event_listener EventsManager::getNextEventListener( ecs_size_t& pIdx, event_listeners_storage& listenersStorage )
    {
        ecs_SpinLock lock( &listenersStorage.mMutex );

        if ( !listenersStorage.mItem.empty() && listenersStorage.mItem.size() < pIdx + 1 )
        {
            pIdx++;
            return listenersStorage.mItem[pIdx];
        }

        return event_listener( nullptr );
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    char EventsManager::handleEvent( event_ptr& pEvent, const bool pAsync, const ecs_uint8_t pThread )
    {
        event_listeners_storage& listenersStorage = getEventListeners( pEvent->getTypeID() );

        char result = 0;
        ecs_size_t listenerIdx = 0;
        event_listener eventListener;
        while( (eventListener = getNextEventListener( listenerIdx, listenersStorage )) != nullptr && mEnabled )
        {
            try
            {
                if ( (result = eventListener->OnEvent( pEvent, pAsync, pThread )) != 0 )
                    break;
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) // DEBUG
                ecs_String logMsg = u8"EventsManager::handleEvent: ERROR ";
                logMsg += pException.what();
                ecs_log::Print( logMsg.c_str(), ecs_log_level::Error );
#endif // DEBUG
                pEvent->onError( pEvent, pException, pAsync, pThread );
                result = -1;
            }
        }

        pEvent->onSend( pEvent, pAsync, pThread );

        return result;
    }

    void EventsManager::Subscribe( const ecs_TypeID eventType, event_listener& pListener )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_assert( pListener != nullptr && "EventsManager::Subscribe: listener argument is null." );
        ecs_assert( eventType > 0 && eventType < ECS_INVALID_TYPE_ID && "EventsManager::Subscribe: Invalid Type-ID." );
#endif // DEBUG

        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        event_listeners_storage& listeners = instance->getEventListeners( eventType );
        ecs_SpinLock lock( &listeners.mMutex );

#if defined( DEBUG ) // DEBUG
        ecs_assert( !ecs_VectorUtil<event_listener>::Find( listeners.mItem, pListener, nullptr ) && "EventsManager::Subscribe - already stored." );
#else // !DEBUG
        if ( ecs_VectorUtil<event_listener>::Find(listeners.mItem, pListener, nullptr) )
            return;
#endif // DEBUG

        listeners.mItem.push_back( pListener );
    }

    void EventsManager::Unsubscribe( const ecs_TypeID eventType, event_listener& pListener )
    {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
        ecs_assert( pListener != nullptr && "EventsManager::Unsubscribe: listener argument is null." );
        ecs_assert( eventType > 0 && eventType < ECS_INVALID_TYPE_ID && "EventsManager::Unsubscribe: Invalid Type-ID." );
#endif // DEBUG

        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        event_listeners_storage& listeners = instance->getEventListeners( eventType );
        ecs_SpinLock lock( &listeners.mMutex );

        ecs_VectorUtil<event_listener>::SwapPop( listeners.mItem, pListener );
    }

    char EventsManager::sendEvent( event_ptr& pEvent, const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance != nullptr )
            return instance->handleEvent( pEvent, false, pThread );

        return 0;
    }

    void EventsManager::queueEvent( event_ptr& pEvent, const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        events_queues_storage& eventsStorage = instance->getEventsQueue( pThread );
        ecs_SpinLock lock( &eventsStorage.mMutex );
        eventsStorage.mItem.push_back( pEvent );
    }

    void EventsManager::Update( const ecs_uint8_t pThread )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        events_queues_storage& eventsStorage = instance->getEventsQueue( pThread );
        event_ptr event;

        while( ( event = getNextEvent(eventsStorage) ) != nullptr && instance->mEnabled )
            instance->handleEvent( event, true, pThread );
    }

    ecs_ObjectID EventsManager::generateEventID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<EventsManager> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mIDMutex );
            return instance->mIDStorage.getAvailableID(pType);
        }

        return ECS_INVALID_OBJECT_ID;
    }

    void EventsManager::releaseEventID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<EventsManager> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mIDMutex );
            instance->mIDStorage.releaseID(pType, pID);
        }
    }

    ECS_API void EventsManager::Initialize()
    {
        if ( mInstance == nullptr )
            mInstance = ecs_new<EventsManager>();
    }

    ECS_API void EventsManager::Terminate()
    {
        if ( mInstance != nullptr )
            mInstance->mEnabled = false;

        mInstance = nullptr;
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
