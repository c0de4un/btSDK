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

#ifndef BT_GL_I_SURFACE_LISTENER_HXX
#define BT_GL_I_SURFACE_LISTENER_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare bt::core::GraphicsSettings
#ifndef BT_CORE_GRAPHICS_SETTINGS_DECL
#define BT_CORE_GRAPHICS_SETTINGS_DECL
namespace bt { namespace core { struct GraphicsSettings; } }
using bt_GraphicsSettings = bt::core::GraphicsSettings;
#endif // !BT_CORE_GRAPHICS_SETTINGS_DECL

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
         * IGLSurfaceListener - interface for OpenGL Surface users.
         *
         * @version 0.1
        **/
        BT_API class IGLSurfaceListener
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_INTERFACE

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * IGLSurfaceListener destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~IGLSurfaceListener() = default;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called when OpenGL Surface is ready (created/changed || restored).
             *
             * @thread_safety - render-thread only.
             * @param pSettings - OpenGL Surface params (width-height, color-depth, stencil, etc).
             * @return - 'true' to continue, 'false' if error.
             * @throws - can throw exception.
            **/
            virtual bool onGLSurfaceReady( const bt_GraphicsSettings* const pSettings ) = 0;

            /**
             * @brief
             * Called every time OpenGL Surface frame is drawn.
             *
             * @thread_safety - render-thread only.
             * @throws - can throw exception.
            **/
            virtual void onGLSurfaceDraw() = 0;

            // -----------------------------------------------------------

        }; /// bt::gl::IGLSurfaceListener

        // -----------------------------------------------------------

    } /// bt::gl

} /// bt

using bt_IGLSurfaceListener = bt::gl::IGLSurfaceListener;
#define BT_GL_I_SURFACE_LISTENER_DECL

// -----------------------------------------------------------

#endif // !BT_GL_I_SURFACE_LISTENER_HXX