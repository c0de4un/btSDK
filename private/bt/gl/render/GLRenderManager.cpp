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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_GL_RENDER_MANAGER_HPP
#include "../../../../public/bt/gl/render/GLRendererManager.hpp"
#endif // !BT_GL_RENDER_MANAGER_HPP

// Include OpenGL API
#ifndef BT_CFG_OPEN_GL_HPP
#include "../../../../public/bt/cfg/bt_open_gl.hpp"
#endif // !BT_CFG_OPEN_GL_HPP

// Include bt::gl::GLSurfaceDrawEvent
#ifndef BT_GL_SURFACE_DRAW_EVENT_HPP
#include "../../../../public/bt/gl/render/events/GLSurfaceDrawEvent.hpp"
#endif // !BT_GL_SURFACE_DRAW_EVENT_HPP

// Include bt::gl::GLSurfaceReadyEvent
#ifndef BT_GL_SURFACE_READY_EVENT_HPP
#include "../../../../public/bt/gl/render/events/GLSurfaceReadyEvent.hpp"
#endif // !BT_GL_SURFACE_READY_EVENT_HPP

// Include bt::core::EThreadTypes
#ifndef BT_CFG_THREADS_HPP
#include "../../../../public/bt/cfg/bt_threads.hpp"
#endif // !BT_CFG_THREADS_HPP

// Include bt::events
#ifndef BT_CFG_EVENTS_HPP
#include "../../../../public/bt/cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

// Include ecs::EventsManager
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../../public/bt/cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

// DEBUG
#if defined( DEBUG ) || defined( BT_DEBUG )

// Include bt::asserts
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

#endif
// DEBUG

// ===========================================================
// bt::gl::GLRenderManager
// ===========================================================

namespace bt
{

    namespace gl
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        GLRenderManager::GLRenderManager() BT_NOEXCEPT
            : RenderManager(),
            mSurfaceReady( false ),
              mGLSurfaceDrawEvent(nullptr)
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager created", bt_ELogLevel::Info );
#endif // DEBUG
        }

        GLRenderManager::~GLRenderManager() BT_NOEXCEPT
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager destructed", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        void GLRenderManager::setSurfaceColor( const bt_Color4f& pColor ) BT_NOEXCEPT
        {
            RenderManager::setSurfaceColor( pColor );
            glClearColor( mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a );
        }

        // ===========================================================
        // bt::core::IGraphicsListener
        // ===========================================================

        bool GLRenderManager::onGLSurfaceReady(const bt_GraphicsSettings* const pSettings)
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onSurfaceReady", bt_ELogLevel::Info );
#endif // DEBUG

            // Update Surface-Color.
            glClearColor( mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a );

            // Guarded-Block
            try
            {
                // Send GLSurfaceReadyEvent
                bt_sptr<ecs_IEvent> surfaceReadyEvent = bt_SharedCast<ecs_IEvent, bt_GLSurfaceReadyEvent>( bt_Shared<bt_GLSurfaceReadyEvent>(mSurfaceReady) );
                if ( ecs_Event::Send( surfaceReadyEvent, false, static_cast<ecs_uint8_t>(bt_EThreadTypes::Render) ) < 0 )
                {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                    bt_Log::Print(u8"GLRenderManager::onSurfaceReady - Failed to send Event.", bt_ELogLevel::Warning );
#endif // DEBUG

                    return false;
                }

                // Create GLSurfaceDrawEvent
                mGLSurfaceDrawEvent = bt_SharedCast<ecs_IEvent, bt_GLSurfaceDrawEvent>( bt_Shared<bt_GLSurfaceDrawEvent>(0) );
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg( u8"GLRenderManager::onSurfaceReady - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                return false;
            }

            // Set Surface-Ready flag.
            mSurfaceReady = true;

            // OK
            return true;
        }

        void GLRenderManager::onGLSurfaceDraw()
        {
            // Cancel if not Started || Paused.
            if ( !isStarted() || isPaused() )
                return;

            // Clear Surface.
            glClear( GL_COLOR_BUFFER_BIT );

            // Guarded-Block
            try
            {
                // Send GLSurfaceDrawEvent
                ecs_Event::Send( mGLSurfaceDrawEvent, false, static_cast<ecs_uint8_t>(bt_EThreadTypes::Render) );
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg( u8"GLRenderManager::onSurfaceReady - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG
                // Re-throw
                throw;
            }
        }

        // ===========================================================
        // bt::core::RenderManager
        // ===========================================================

        bool GLRenderManager::onStart()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onStart", bt_ELogLevel::Info );
#endif // DEBUG

            return RenderManager::onStart();
        }

        bool GLRenderManager::onResume()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            return RenderManager::onResume();
        }

        void GLRenderManager::onPause()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            RenderManager::onPause();
        }

        void GLRenderManager::onStop()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Release GLSurfaceDrawEvent
            mGLSurfaceDrawEvent = nullptr;

            RenderManager::onStop();
        }

        // -----------------------------------------------------------

    } /// bt::gl

} /// bt

// -----------------------------------------------------------
