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

#ifndef ECS_EVENTS_MANAGER_HPP
#define ECS_EVENTS_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::ids
#ifndef ECS_IDS_HPP
#include "../types/ecs_ids.hpp"
#endif // !ECS_IDS_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "../types/ecs_mutex.hpp"
#endif // ECS_MUTEX_HPP

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// Include ecs::map
#ifndef ECS_MAP_HPP
#include "../types/ecs_map.hpp"
#endif // !ECS_MAP_HPP

// Include ecs::deque
#ifndef ECS_DEQUE_HPP
#include "../types/ecs_queue.hpp"
#endif // !ECS_DEQUE_HPP

// Include ecs::vector
#ifndef ECS_VECTOR_HPP
#include "../types/ecs_vector.hpp"
#endif // !ECS_VECTOR_HPP

// ===========================================================
// FORWARD-DECLARATION
// ===========================================================

// Forward-Declare ecs::IEvent
#ifndef ECS_I_EVENT_DECL
#define ECS_I_EVENT_DECL
namespace ecs { class IEvent; }
using ecs_IEvent = ecs::IEvent;
#endif // !ECS_I_SYSTEM_DECL

// Forward-Declare ecs::IEventListener
#ifndef ECS_I_EVENT_LISTENER_DECL
#define ECS_I_EVENT_LISTENER_DECL
namespace ecs { class IEventListener; }
using ecs_IEventListener = ecs::IEventListener;
#endif // !ECS_I_EVENT_LISTENER_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * EventsManager - Events Manager.
     *
     * @version 0.1
    **/
    class ECS_API EventsManager
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_CLASS

        // -----------------------------------------------------------

    private:

        // -----------------------------------------------------------

        // ===========================================================
        // TYPES
        // ===========================================================

        using event_t = ecs_sptr<ecs_IEvent>;

        using events_deque = ecs_AsyncDeque<event_t>;

        using events_map = ecs_AsyncMap<unsigned char, events_deque>;

        using event_listener = ecs_sptr<ecs_IEventListener>;

        using event_listeners_list = ecs_AsyncVector<event_listener>;

        using event_listeners_typed_map = ecs_AsyncMap<ecs_TypeID, event_listeners_list>;

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** EventsManager instance. **/
        static ecs_sptr<EventsManager> mInstance;

        /** IDStorage **/
        ecs_IDMap<ecs_TypeID, ecs_ObjectID> mIDStorage;

        /** Events queue. **/
        events_map mEventsByThread;

        /** Event Listeners. **/
        event_listeners_typed_map mEventListeners;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns weak-pointer to EventsManager isntance.
         *
         * @thread_safety - thread-safe due to atomic nature.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_sptr<EventsManager> getInstance();

        /**
         * @brief
         * Returns Events queue for thread.
         *
         * @thread_safety - thread-locks used.
         * @param pThread - Thread-Type. 0 for default.
         * @return - Events queue.
         * @throws - can throw exception.
        **/
        events_deque& getEventsQueue( const unsigned char pThread );

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Handle Event.
         *
         * @thread_safety - thread-locks used.
         * @param pEvent - Event to send.
         * @param pThread - thread-type, default is 0 to via update-thread.
         * @return 0 to continue, 1 if handled to stop, -1 if error.
         * @throws - can throw exception. Errors collected & reported.
        **/
        char handleEvent( ecs_sptr<ecs_IEvent>& pEvent, const ecs_uint8_t pThread );

        // ===========================================================
        // DELETED
        // ===========================================================

        EventsManager(const EventsManager&) = delete;
        EventsManager& operator=(const EventsManager&) = delete;
        EventsManager(EventsManager&&) = delete;
        EventsManager& operator=(EventsManager&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * EventsManager constructor.
         *
         * @throws - can throw exception.
        **/
        explicit EventsManager();

        /**
         * @brief
         * EventsManager destructor.
         *
         * @throws - can throw exception.
        **/
        ~EventsManager();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================



        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Subscribes Event Listener for specific Event-Type.
         *
         * @thread_safety - thread-locks used.
         * @param eventType - Event Type-ID.
         * @param pListener - IEventListener implementation.
         * @throws - can throw exception.
        **/
        static void Subscribe( const ecs_TypeID eventType, ecs_sptr<ecs_IEventListener> pListener );

        /**
         * @brief
         * Unsubscribe Event Listener from Event-Type.
         *
         * @thread_safety - thread-locks used.
         * @param eventType - Event Type-ID.
         * @param pListener - IEventListener implementation.
         * @throws - can throw exception.
        **/
        static void Unsubscribe( const ecs_TypeID eventType, ecs_sptr<ecs_IEventListener>& pListener );

        /**
         * @brief
         * Send Event now.
         *
         * @thread_safety - thread-locks used.
         * @param pEvent - Event to send.
         * @param pThread - thread-type, default is 0 to via update-thread.
         * @return 0 to continue, 1 if handled to stop, -1 if error.
         * @throws - can throw exception. Errors collected & reported.
        **/
        static char sendEvent( ecs_sptr<ecs_IEvent> pEvent, const ecs_uint8_t pThread = 0 );

        /**
         * @brief
         * Send delayed Event.
         *
         * @thread_safety - thread-locks used.
         * @param pEvent - Event to queue.
         * @param pThread - thread-type, default is 0 to via update-thread.
         * @throws - can throw exception.
        **/
        static void queueEvent( ecs_sptr<ecs_IEvent> pEvent, const ecs_uint8_t pThread = 0 );

        /**
         * @brief
         * Send all queued Events.
         *
         * @thread_safety - thread-locks used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception. All errors collected & reported.
        **/
        static void Update( const ecs_uint8_t pThread );

        /**
         * @brief
         * Returns Event ID.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        static ecs_ObjectID generateEventID(const ecs_TypeID pType) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns Event ID for re-usage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID to return for reuse.
         * @throws - can throw exception.
        **/
        static void releaseEventID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT;

        /**
         * @brief
         * Initialize EventsManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Initialize();

        /**
         * @brief
         * Terminate EventsManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Terminate();

        // -----------------------------------------------------------

    }; /// ecs::EventsManager

    // -----------------------------------------------------------

} /// ecs

using ecs_EventsManager = ecs::EventsManager;
#define ECS_EVENTS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !ECS_EVENTS_MANAGER_HPP
