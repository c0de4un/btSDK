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

#ifndef BT_GL_SURFACE_READY_EVENT_HPP
#define BT_GL_SURFACE_READY_EVENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::SurfaceReadyEvent
#ifndef BT_CORE_SURFACE_READY_EVENT_HPP
#include "../../../core/render/events/SurfaceReadyEvent.hpp"
#endif // !BT_CORE_SURFACE_READY_EVENT_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace gl
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * GLSurfaceReadyEvent - called when OpenGL Surface created/changed or restored.
         *
         * @version 0.1
        **/
        BT_API class GLSurfaceReadyEvent final : public bt_SurfaceReady
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

            GLSurfaceReadyEvent(const GLSurfaceReadyEvent&) = delete;
            GLSurfaceReadyEvent& operator=(const GLSurfaceReadyEvent&) = delete;
            GLSurfaceReadyEvent(GLSurfaceReadyEvent&&) = delete;
            GLSurfaceReadyEvent& operator=(GLSurfaceReadyEvent&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * GLSurfaceReadyEvent constructor.
             *
             * @param surfaceRestored - 'true' if surface changed/update or restored.
             * @throws - can throw exception:
             *           - mutex;
            **/
            explicit GLSurfaceReadyEvent( const bool surfaceRestored );

            /**
             * @brief
             * GLSurfaceDrawEvent destructor.
             *
             * @throws - can throw exception:
             *           - mutex;
            **/
            virtual ~GLSurfaceReadyEvent();

            // -----------------------------------------------------------

        }; /// bt::gl::GLSurfaceDrawEvent

        // -----------------------------------------------------------

    } /// bt::gl

} /// bt

using bt_GLSurfaceReadyEvent = bt::gl::GLSurfaceReadyEvent;

// -----------------------------------------------------------

#endif // !BT_GL_SURFACE_READY_EVENT_HPP