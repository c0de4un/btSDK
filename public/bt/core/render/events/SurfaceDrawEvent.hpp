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

#ifndef BT_CORE_SURFACE_DRAW_EVENT_HPP
#define BT_CORE_SURFACE_DRAW_EVENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::Event
#ifndef ECS_COMPONENT_HPP
#include "../../../ecs/event/Event.hpp"
#endif // !ECS_COMPONENT_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * SurfaceDrawEvent - event to send on every frame draw.
         *
         * @version 0.1
        **/
        class BT_API SurfaceDrawEvent final : public ecs_Event
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_CLASS

            // -----------------------------------------------------------

        private:

            // -----------------------------------------------------------

            // ===========================================================
            // DELETED
            // ===========================================================

            SurfaceDrawEvent(const SurfaceDrawEvent&) = delete;
            SurfaceDrawEvent& operator=(const SurfaceDrawEvent&) = delete;
            SurfaceDrawEvent(SurfaceDrawEvent&&) = delete;
            SurfaceDrawEvent& operator=(SurfaceDrawEvent&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTANTS
            // ===========================================================

            /** Thread-Type. **/
            const unsigned char mThreadType;

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * SurfaceDrawEvent constructor.
             *
             * @param pThread - Thread-Type.
             * @throws - can throw exception:
             *           - mutex;
            **/
            explicit SurfaceDrawEvent( const unsigned char pThread );

            /**
             * @brief
             * SurfaceDrawEvent destructor.
             *
             * @throws - can throw exception:
             *           - mutex;
            **/
            virtual ~SurfaceDrawEvent();

            // -----------------------------------------------------------

        };

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_SurfaceDrawEvent = bt::core::SurfaceDrawEvent;
#define BT_CORE_SURFACE_DRAW_EVENT_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_SURFACE_DRAW_EVENT_HPP