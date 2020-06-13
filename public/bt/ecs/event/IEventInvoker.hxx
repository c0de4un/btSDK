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

#ifndef BT_CORE_I_EVENT_INVOKER_HXX
#define BT_CORE_I_EVENT_INVOKER_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare ecs::IEvent
#ifndef ECS_I_EVENT_DECL
#define ECS_I_EVENT_DECL
namespace ecs { class IEvent; }
using ecs_IEvent = ecs::IEvent;
#endif // !ECS_I_SYSTEM_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * IEventInvoker - allows to notify Event sender about completion.
     *
     * @version 0.1
    **/
    class ECS_API IEventInvoker
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_INTERFACE

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * IEventInvoker destructor.
        **/
        virtual ~IEventInvoker() = default;

        // ===========================================================
        // METHODS
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
        virtual void onEventSent( ecs_sptr<ecs_IEvent>& pEvent, const bool pAsync, const ecs_uint8_t pThread ) = 0;

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
        virtual void onEventSentError( ecs_sptr<ecs_IEvent>& pEvent, const std::exception& pException, const bool pAsync, const ecs_uint8_t pThread ) = 0;

        // -----------------------------------------------------------

    }; /// ecs::IEventInvoker

    // -----------------------------------------------------------

} /// ecs

using ecs_IEventInvoker = ecs::IEventInvoker;
#define BT_CORE_I_EVENT_INVOKER_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_I_EVENT_INVOKER_HXX
