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

#ifndef ECS_COMPONENT_HPP
#define ECS_COMPONENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// Include ecs::atomic
#ifndef ECS_ATOMIC_HPP
#include "../types/ecs_atomic.hpp"
#endif // !ECS_ATOMIC_HPP

// ===========================================================
// FORWARD-DECLARATION
// ===========================================================

// Forward-Declare ecs::IEventInvoker
#ifndef BT_CORE_I_EVENT_INVOKER_DECL
#define BT_CORE_I_EVENT_INVOKER_DECL
namespace ecs { class IEventInvoker; }
using ecs_IEventInvoker = ecs::IEventInvoker;
#endif // !BT_CORE_I_EVENT_INVOKER_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * Event - base Event class.
     *
     * @version 0.1
    **/
    class ECS_API Event : public ecs_IEvent
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

        /** Type-ID. **/
        const ecs_TypeID mTypeID;

        /** Instance-ID. **/
        const ecs_ObjectID mID;

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** Event Invoker (caller). **/
        ecs_wptr<ecs_IEventInvoker> mInvoker;

        // ===========================================================
        // CONSTRUCTOR
        // ===========================================================

        /**
         * @brief
         * Event constructor.
         *
         * @param pType - Event-Type.
         * @param pRepeat - 'true' if Event repeats.
         * @param pCaller - Event Invoker.
         * @throws - can throw exception.
        **/
        explicit Event( const ecs_TypeID pType, const bool pRepeat = true, ecs_wptr<ecs_IEventInvoker> pCaller = ecs_wptr<ecs_IEventInvoker>() );

        // ===========================================================
        // DELETED
        // ===========================================================

        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;
        Event(Event&&) = delete;
        Event& operator=(Event&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** Handled-flag. **/
        ecs_atomic<bool> mHandled;

        /** Repeat-flag. **/
        bool mRepeatable;

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * Event destructor.
         *
         * @throws - can throw exception.
        **/
        virtual ~Event();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Set repeat-flag.
         *
         * @thread_safety - not required.
         * @param pRepeat - 'true' to repeate Event until it's removed,
         * 'false' to remove after sending.
         * @throws - no exception.
        **/
        void setRepeat( const bool pRepeat ) ECS_NOEXCEPT;

        // ===========================================================
        // ecs::IEvent
        // ===========================================================

        /**
         * @brief
         * Returns Event Type-ID.
         *
         * @thread_safety - no required.
         * @throws - no exception.
        **/
        virtual ecs_TypeID getTypeID() const ECS_NOEXCEPT final;

        /**
         * @brief
         * Returns Event IEntity ID.
         *
         * @thread_safety - no required.
         * @throws - no exception.
        **/
        virtual ecs_ObjectID getID() const ECS_NOEXCEPT final;

        /**
         * @brief
         * Returns 'true' if Event already handled.
         *
         * @thread_safety - atomics used.
         * @throws - no exceptions.
        **/
        virtual bool isHandled() const ECS_NOEXCEPT final;

        /**
         * @brief
         * Returns 'true' if Event repeats until manually removed.
         *
         * (?) Allows to avoid allocating Events
         *
         * @thread_safety
        **/
        virtual bool isRepeatable() const ECS_NOEXCEPT final;

        /**
         * @brief
         * Called when Event caught error.
         *
         * @thread_safety - not thread-safe.
         * @param pEvent - this.
         * @param pException - exception.
         * @param pAsync - 'true' if Async-sending used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception.
        **/
        virtual void onError( ecs_sptr<IEvent>& pEvent, const std::exception& pException, const bool pAsync, const unsigned pThread ) override;

        /**
         * @brief
         * Called when Event sent.
         *
         * @thread_safety - not thread-safe.
         * @param pEvent - this.
         * @param pAsync - 'true' if Async-sending used.
         * @param pThread - Thread-Type.
         * @throws - can throw exception.
        **/
        virtual void onSend( ecs_sptr<IEvent>& pEvent, const bool pAsync, const unsigned pThread ) override;

        /**
         * @brief
         * Send this Event.
         *
         * (?) Wrapper/utility method.
         *
         * @thread_safety - not required.
         * @param pEvent - Event to send.
         * @param pAsync - 'true' to queue Event sending, 'false' to handle right now with thread-locks.
         * @throws - unlikely, but can throw unhandled exception, error though collected & reported.
        **/
        static ECS_API char Send( ecs_sptr<IEvent>& pEvent, const bool pAsync = true, const ecs_uint8_t pThread = 0 );

        // -----------------------------------------------------------

    }; /// ecs::Event

    // -----------------------------------------------------------

} /// ecs

using ecs_Event = ecs::Event;
#define ECS_COMPONENT_DECL

// -----------------------------------------------------------

#endif // !ECS_COMPONENT_HPP
