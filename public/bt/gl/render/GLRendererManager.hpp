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

#ifndef BT_GL_RENDER_MANAGER_HPP
#define BT_GL_RENDER_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::Render
#ifndef BT_CORE_RENDER_MANAGER_HPP
#include "../../core/render/RenderManager.hpp"
#endif // !BT_CORE_RENDER_MANAGER_HPP

// Include ecs::IEventInvoker
#ifndef BT_CORE_I_EVENT_INVOKER_HXX
#include "../../ecs/event/IEventInvoker.hxx"
#endif // !BT_CORE_I_EVENT_INVOKER_HXX

// Include ecs::IEventListener
#ifndef ECS_I_EVENT_LISTENER_HXX
#include "../../ecs/event/IEventListener.hxx"
#endif // !ECS_I_EVENT_LISTENER_HXX

// Include bt::gl::IGLSurfaceListener
#ifndef BT_GL_I_SURFACE_LISTENER_HXX
#include "../../gl/render/IGLSurfaceListener.hxx"
#endif // !BT_GL_I_SURFACE_LISTENER_HXX

// Include bt::gl::GLSurfaceDrawEvent
#ifndef BT_GL_SURFACE_DRAW_EVENT_HPP
#include "events/GLSurfaceDrawEvent.hpp"
#endif // !BT_GL_SURFACE_DRAW_EVENT_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace gl
    {

        /**
         * @brief
         * GLRenderManager - renderer class for OpenGL (& ES) API.
         *
         * @version 0.1
        **/
        class BT_API GLRenderManager final : public bt_RenderManager, public bt_IGLSurfaceListener
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

            /** Surface-Ready flag. **/
            bt_atomic<bool> mSurfaceReady;

            /** OpenGL Draw-Event. **/
            bt_sptr<ecs_IEvent> mGLSurfaceDrawEvent;

            // -----------------------------------------------------------

        protected:

            // -----------------------------------------------------------

            // ===========================================================
            // DELETED
            // ===========================================================

            GLRenderManager(const GLRenderManager&) = delete;
            GLRenderManager& operator=(const GLRenderManager&) = delete;
            GLRenderManager(GLRenderManager&&) = delete;
            GLRenderManager& operator=(GLRenderManager&&) = delete;

            // ===========================================================
            // bt::core::RenderManager
            // ===========================================================

            /**
             * @brief
             * Called when RenderManager starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() final;

            /**
             * @brief
             * Called whe RenderManager resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() final;

            /**
             * @brief
             * Called whe RenderManager pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() final;

            /**
             * @brief
             * Called whe RenderManager stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() final;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * GLRenderManager constructor.
             *
             * @throws - no exceptions.
            **/
            explicit GLRenderManager() BT_NOEXCEPT;

            /**
             * @brief
             * GLRenderManager destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~GLRenderManager() BT_NOEXCEPT;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Set Surface clear-color.
             *
             * @thread_safety - render thread-only.
             * @param pColor - color. Value copied/moved.
             * @throws - no exceptions.
            **/
            virtual void setSurfaceColor( const bt_Color4f& pColor ) BT_NOEXCEPT final;

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
            virtual bool onGLSurfaceReady( const bt_GraphicsSettings* const pSettings ) final;

            /**
             * @brief
             * Called every time OpenGL Surface frame is drawn.
             *
             * @thread_safety - render-thread only.
             * @throws - can throw exception.
            **/
            virtual void onGLSurfaceDraw() final;

            // -----------------------------------------------------------

        }; /// bt::gl::GLRenderManager

    } /// bt::gl

} /// bt

using bt_GLRenderManager = bt::gl::GLRenderManager;
#define BT_GL_RENDER_MANAGER_DECL

// -----------------------------------------------------------

#endif // !BT_GL_RENDER_MANAGER_HPP
