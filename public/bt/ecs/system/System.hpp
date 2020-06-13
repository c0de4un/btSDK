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

#ifndef ECS_SYSTEM_HPP
#define ECS_SYSTEM_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::ISystem
#ifndef ECS_I_SYSTEM_HXX
#include "ISystem.hxx"
#endif // !ECS_I_SYSTEM_HXX

// Include ecs::IEventListener
#ifndef ECS_I_EVENT_LISTENER_HXX
#include "../event/IEventListener.hxx"
#endif // !ECS_I_EVENT_LISTENER_HXX

// Include ecs::IEventInvoker
#ifndef BT_CORE_I_EVENT_INVOKER_HXX
#include "../event/IEventInvoker.hxx"
#endif // !BT_CORE_I_EVENT_INVOKER_HXX

// Include ecs::atomic
#ifndef ECS_ATOMIC_HPP
#include "../types/ecs_atomic.hpp"
#endif // !ECS_ATOMIC_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "../types/ecs_mutex.hpp"
#endif // !ECS_MUTEX_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * System - base System class.
     *
     * @version 0.1
    **/
    class ECS_API System : public ecs_ISystem, public ecs_IEventListener, public ecs_IEventInvoker
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_CLASS

        // -----------------------------------------------------------

    protected:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTANTS
        // ===========================================================

        static constexpr const unsigned char SYSTEM_STATE_NOT_STARTED = 0;
        static constexpr const unsigned char SYSTEM_STATE_STARTING = 1;
        static constexpr const unsigned char SYSTEM_STATE_STARTED = 2;
        static constexpr const unsigned char SYSTEM_STATE_PAUSING = 3;
        static constexpr const unsigned char SYSTEM_STATE_PAUSED = 4;
        static constexpr const unsigned char SYSTEM_STATE_RESUMING = 5;
        static constexpr const unsigned char SYSTEM_STATE_STOPPING = 6;
        static constexpr const unsigned char SYSTEM_STATE_STOPPED = 7;

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** Mutex to synchronize state-value access. **/
        mutable ecs_Mutex mStateMutex;

        /** State. **/
        ecs_atomic<unsigned char> mCurrentState;

        // ===========================================================
        // CONSTRUCTOR
        // ===========================================================

        /**
         * @brief
         * System constructor.
         *
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        explicit System( const ecs_TypeID pType );

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns current state.
         *
         * @thread_safety - atomics used.
         * @throws - no exceptions.
        **/
        unsigned char getState() const;

        /**
         * @brief
         * Sets new state.
         *
         * @thread_safety - atomics used.
         * @returns - 'true' if state set, false if no need.
         * @throws - no exceptions.
        **/
        bool setState( const unsigned char newState );

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Called when System starting.
         *
         * @thread_safety - thread-lock used.
         * @throws - can throw exception.
        **/
        virtual bool onStart();

        /**
         * @brief
         * Called whe System resuming from pause.
         *
         * @thread_safety - thread-lock used.
         * @throws - can throw exception.
        **/
        virtual bool onResume();

        /**
         * @brief
         * Called whe System pausing.
         *
         * @thread_safety - thread-lock used.
         * @throws - can throw exception.
        **/
        virtual void onPause();

        /**
         * @brief
         * Called whe System stopping.
         *
         * @thread_safety - thread-lock used.
         * @throws - can throw exception.
        **/
        virtual void onStop();

        // ===========================================================
        // DELETED
        // ===========================================================

        System(const System&) = delete;
        System& operator=(const System&) = delete;
        System(System&&) = delete;
        System& operator=(System&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTANTS
        // ===========================================================

        /** Type-ID. **/
        const ecs_TypeID mTypeID;

        /** ID. **/
        const ecs_ObjectID mID;

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * System constructor.
         *
         * @throws - can throw exception.
        **/
        virtual ~System();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns Type-ID.
         *
         * @thread_safety - not required.
         * @throws - no exceptions.
        **/
        virtual ecs_TypeID getTypeID() const BT_NOEXCEPT override;

        /**
         * @brief
         * Returns System ID.
         *
         * @throws - no exceptions.
        **/
        virtual ecs_ObjectID getID() const BT_NOEXCEPT final;

        /**
         * @brief
         * Returns 'true' if paused.
         *
         * @thread_safety - atomic used.
         * @throws - no exceptions.
        **/
        virtual bool isPaused() const noexcept final;

        /**
         * @brief
         * Returns 'true' if System started.
         *
         * @thread_safety - atomic used.
         * @throws - no exceptions.
        **/
        virtual bool isStarted() const noexcept final;

        // ===========================================================
        // ecs::ISystem
        // ===========================================================

        /**
         * @brief
         * Start/Resume System.
         *
         * @thread_safety - thread-locks used.
         * @return - 'true' if OK, 'false' if error.
         * @throws - can throw exception.
        **/
        virtual bool Start() final;

        /**
         * @brief
         * Pause System.
         *
         * @thread_safety - thread-locks used.
         * @throws - can throw exception.
        **/
        virtual void Pause() final;

        /**
         * @brief
         * Stop System.
         * Unlikely #Pause, release (unload) all related resources.
         *
         * @thread_safety - thread-locks used.
         * @throws - no exceptions.
        **/
        virtual void Stop() final;

        // ===========================================================
        // ecs::IEventListener
        // ===========================================================

        /**
         * @brief
         * Called on Event.
         *
         * @thread_safety - depends on implementation.
         * @param pEvent - Event to handle.
         * @param pAsync - 'true' if called in Async-mode.
         * @param pThread - Thread-Type.
         * @return - 0 to continue, 1 if handled to stop, -1 if error.
         * @throws - can throw exception. Exceptions collected & reported.
        **/
        virtual char OnEvent( ecs_sptr<ecs_IEvent> pEvent, const bool pAsync, const unsigned char pThread ) override;

        /**
         * @brief
         * Called on Event Error.
         *
         * @thread_safety - depends on implementation.
         * @param pEvent - Event to handle.
         * @param pException - Exception.
         * @param pAsync - 'true' if called in Async-mode.
         * @param pThread - Thread-Type.
         * @return - 0 to continue, 1 if handled to stop, -1 if error.
         * @throws - can throw exception. Exceptions collected & reported.
        **/
        virtual void onEventError( ecs_sptr<ecs_IEvent> pEvent, const std::exception& pException, const bool pAsync, const unsigned char pThread ) override;

        // ===========================================================
        // ecs::IEventInvoker
        // ===========================================================

        /**
         * @brief
         * Called when Event sent.
         *
         * @thread_safety - not required.
         * @param pEvent - Event.
         * @param pAsync - 'true' if Async-sending used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception. Errors collected & reported.
        **/
        virtual void onEventSent( ecs_sptr<ecs_IEvent>& pEvent, const bool pAsync, const ecs_uint8_t pThread ) override;

        /**
         * @brief
         * Called when Event caught error.
         *
         * @thread_safety - not thread-safe.
         * @param pEvent - Event.
         * @param pException - Exception.
         * @param pAsync - 'true' if Async-sending used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception. Errors collected & reported.
        **/
        virtual void onEventSentError( ecs_sptr<ecs_IEvent>& pEvent, const std::exception& pException, const bool pAsync, const ecs_uint8_t pThread ) override;

        // -----------------------------------------------------------

    }; /// ecs::System

    // -----------------------------------------------------------

} /// ecs

using ecs_System = ecs::System;

#define ECS_SYSTEM_DECL

// -----------------------------------------------------------

#endif // !ECS_COMPONENT_HPP
