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

// Include ecs::atomic
#ifndef ECS_ATOMIC_HPP
#include "../types/ecs_atomic.hpp"
#endif // !ECS_ATOMIC_HPP

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

        /** Event Pointer-type. **/
        using event_ptr = ecs_sptr<ecs_IEvent>;

        /** Events queue container. **/
        using events_queue = ecs_deque<event_ptr>;

        /** Events Queues Storage. **/
        using events_queues_storage = ecs_AsyncStorage<events_queue>;

        /** Events Typed map. **/
        using events_queues_map = ecs_map<unsigned char, events_queues_storage>;

        /** Event Listener Pointer. **/
        using event_listener = ecs_sptr<ecs_IEventListener>;

        /** Event Listeners vector. **/
        using event_listeners_vector = ecs_vec<event_listener>;

        /** Events Listeners Storage. **/
        using event_listeners_storage = ecs_AsyncStorage<event_listeners_vector>;

        /** Events Listeners Typed map. **/
        using event_listeners_map = ecs_map<ecs_TypeID, event_listeners_storage>;

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** EventsManager instance. **/
        static ecs_sptr<EventsManager> mInstance;

        /** Enabled flag. **/
        ecs_atomic<bool> mEnabled;

        /** IDStorage **/
        ecs_IDMap<ecs_TypeID, ecs_ObjectID> mIDStorage;

        /** IEvents IDs Mutex. **/
        ecs_Mutex mIDMutex;

        /** Events queue. **/
        events_queues_map mEventsByThread;

        /** Events Mutex. **/
        ecs_Mutex mEventsMutex;

        /** Event Listeners. **/
        event_listeners_map mEventListeners;

        /** Event Listeners Mutex. **/
        ecs_Mutex mEventListenersMutex;

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
        events_queues_storage& getEventsQueue( const unsigned char pThread );

        /**
         * @brief
         * Returns Event Listeners container.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Event Type-ID.
         * @throws - can throw exception.
        **/
        event_listeners_storage& getEventListeners( const ecs_TypeID pType );

        /**
         * @brief
         * Returns next Event in queue, or null.
         *
         * @thread_safety - thread-locks used.
         * @throws - can throw exception (mutex).
        **/
        static ECS_API event_ptr getNextEvent( events_queues_storage& eventsStorage );

        /**
         * @brief
         * Returns next Event Listener, or null.
         *
         * @thread_safety - thread-locks used.
         * @throws - can throw exception (mutex).
        **/
        static ECS_API event_listener getNextEventListener( ecs_size_t& pIdx, event_listeners_storage& listenersStorage );

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Handle Event.
         *
         * @thread_safety - thread-locks used.
         * @param pEvent - Event to send.
         * @param pAsync - 'true' if Async-mode.
         * @param pThread - thread-type, default is 0 to via update-thread.
         * @return 0 to continue, 1 if handled to stop, -1 if error.
         * @throws - can throw exception. Errors collected & reported.
        **/
        char handleEvent( event_ptr& pEvent, const bool pAsync, const ecs_uint8_t pThread );

        /**
         * @brief
         * Removes Events from Queue.
         *
         * @thread_safety - thread-locks used.
         * @param eventsStorage - Events queue storage.
         * @param pType - Event Type-ID.
         * @param pID - Event ID. Default is #ECS_INVALID_OBJECT_ID to remove all with Type-ID.
         * @throws - can throw exception (mutex).
        **/
        static ECS_API void removeEvents( events_queues_storage& eventsStorage, const ecs_TypeID pType, const ecs_ObjectID pID = ECS_INVALID_OBJECT_ID );

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
        static ECS_API void Subscribe( const ecs_TypeID eventType, event_listener& pListener );

        /**
         * @brief
         * Subscribes Event Listener for specific Event-Types.
         *
         * @thread_safety - thread-locks used.
         * @param pTypes - Events Type-ID.
         * @param pListener - IEventListener implementation.
         * @throws - can throw exception.
        **/
        static ECS_API void SubscribeBatch( const ecs_vec<ecs_TypeID>& pTypes, event_listener& pListener );

        /**
         * @brief
         * Unsubscribe Event Listener from Event-Type.
         *
         * @thread_safety - thread-locks used.
         * @param eventType - Event Type-ID.
         * @param pListener - IEventListener implementation.
         * @throws - can throw exception.
        **/
        static ECS_API void Unsubscribe( const ecs_TypeID eventType, event_listener& pListener );

        /**
         * @brief
         * Unsubscribe Event Listener from Events-Types.
         *
         * @thread_safety - thread-locks used.
         * @param eventType - Events Type-ID.
         * @param pListener - IEventListener implementation.
         * @throws - can throw exception.
        **/
        static ECS_API void UnsubscribeBatch( const ecs_vec<ecs_TypeID>& pTypes, event_listener& pListener );

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
        static ECS_API char sendEvent( event_ptr& pEvent, const ecs_uint8_t pThread = 0 );

        /**
         * @brief
         * Send delayed Event (Async-mode).
         *
         * @thread_safety - thread-locks used.
         * @param pEvent - Event to queue.
         * @param pThread - thread-type, default is 0 to via update-thread.
         * @throws - can throw exception.
        **/
        static ECS_API void queueEvent( event_ptr& pEvent, const ecs_uint8_t pThread = 0 );

        /**
         * @brief
         * Removes all Events of the given Type.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Event Type-ID.
         * @param pThread - Thread-Type, default is 0 to remove from all Threads.
         * @throws - can throw exception (mutex).
        **/
        static ECS_API void FlushEvents( const ecs_TypeID pType, const unsigned char pThread = 0 );

        /**
         * @brief
         * Removes specific Event from queue.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Event Type-ID.
         * @param pID - Event ID.
         * @param pThread - Thread-Type.
         * @throws - can throw exception (mutex).
        **/
        static ECS_API void RemoveEvent( const ecs_TypeID pType, const ecs_ObjectID pID, const unsigned char pThread );

        /**
         * @brief
         * Send all queued Events.
         *
         * @thread_safety - thread-locks used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception. All errors collected & reported.
        **/
        static ECS_API void Update( const ecs_uint8_t pThread );

        /**
         * @brief
         * Returns Event ID.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_ObjectID generateEventID(const ecs_TypeID pType) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns Event ID for re-usage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID to return for reuse.
         * @throws - can throw exception.
        **/
        static ECS_API void releaseEventID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT;

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

using ecs_Events = ecs::EventsManager;
#define ECS_EVENTS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !ECS_EVENTS_MANAGER_HPP
