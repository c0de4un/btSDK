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

#ifndef BT_ANDROID_GRAPHICS_HPP
#define BT_ANDROID_GRAPHICS_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::GraphicsManager
#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#include "../../core/graphics/GraphicsManager.hpp"
#endif // !BT_CORE_GRAPHICS_MANAGER_HPP

// Include bt::gl::IGLSurfaceListener
#ifndef BT_GL_I_SURFACE_LISTENER_HXX
#include "../../gl/render/IGLSurfaceListener.hxx"
#endif // !BT_GL_I_SURFACE_LISTENER_HXX

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare bt::gl::GLRenderManager
#ifndef BT_GL_RENDER_MANAGER_DECL
#define BT_GL_RENDER_MANAGER_DECL
namespace bt { namespace gl { class GLRenderManager; } }
using bt_GLRenderManager = bt::gl::GLRenderManager;
#endif // !BT_GL_RENDER_MANAGER_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * AndroidGraphics - default graphics manager for Android platform.
         * Handles Android GDI (Windows, Frames, Layouts, Forms, etc).
         *
         * @version 0.1
        **/
        class BT_API AndroidGraphics final : public bt_Graphics, public bt_IGLSurfaceListener
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
            // FIELDS
            // ===========================================================

            /** GLRenderManager **/
            bt_sptr<bt_GLRenderManager> mGLRenderer;

            // ===========================================================
            // DELETED
            // ===========================================================

            AndroidGraphics(const AndroidGraphics&) = delete;
            AndroidGraphics& operator=(const AndroidGraphics&) = delete;
            AndroidGraphics(AndroidGraphics&&) = delete;
            AndroidGraphics& operator=(AndroidGraphics&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AndroidGraphics constructor.
             *
             * @param pSettings - initial Graphics Settings, value copied.
             * @throws - can throw exception.
            **/
            explicit AndroidGraphics( const bt_GraphicsSettings& pSettings );

            /**
             * @brief
             * AndroidGraphics destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~AndroidGraphics();

            // ===========================================================
            // IGLSurfaceListener
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
            virtual bool onGLSurfaceReady( const bt_GraphicsSettings* const pSettings ) final;

            /**
             * @brief
             * Called every time OpenGL Surface frame is drawn.
             *
             * @thread_safety - render-thread only.
             * @throws - can throw exception.
            **/
            virtual void onGLSurfaceDraw() final;

            // ===========================================================
            // bt::core::GraphicsManager
            // ===========================================================

            /**
             * @brief
             * Called when System starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() final;

            /**
             * @brief
             * Called whe System resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() final;

            /**
             * @brief
             * Called whe System pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() final;

            /**
             * @brief
             * Called whe System stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() final;

            // -----------------------------------------------------------

        }; /// bt::android::AndroidGraphics

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_AndroidGraphics = bt::android::AndroidGraphics;

#define BT_ANDROID_GRAPHICS_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_GRAPHICS_HPP
