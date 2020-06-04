/**
 * Copyright © 2020 Denis Z. (code4un@yandex.ru) All rights reserved.
 * Authors: Denis Z. (code4un@yandex.ru)
 * All rights reserved.
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
 */

#ifndef ECS_I_EVENT_LISTENER_HXX
#define ECS_I_EVENT_LISTENER_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// ===========================================================
// FORWARD-DECLARATION
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
     * IEventListener - interface for events handlers/listeners.
     *
     * @version 0.1
    **/
    class ECS_API IEventListener
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
        // DELETED
        // ===========================================================

        /**
         * @brief
         * IEventListener destructor.
         *
         * @throws - can throw exception.
        **/
        virtual ~IEventListener()
        {
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Called on Event.
         *
         * @thread_safety - depends on implementation.
         * @param pEvent - Event to handle.
         * @param pThread - Thread-Type.
         * @return - 'true' if handled, to stop further polling.
         * @throws - can throw exception. Exceptions collected & reported.
        **/
        virtual bool OnEvent( ecs_sptr<ecs_IEvent> pEvent, const unsigned char pThread ) = 0;

        // -----------------------------------------------------------

    }; /// ecs::IEventListener

    // -----------------------------------------------------------

} /// ecs

using ecs_IEventListener = ecs::IEventListener;
#define ECS_I_EVENT_LISTENER_DECL

// -----------------------------------------------------------

#endif // !ECS_I_EVENT_LISTENER_HXX