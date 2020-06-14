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

// Include bt::core::LoadEvent
#ifndef BT_CORE_LOAD_EVENT_HPP
#include "../../../../public/bt/core/render/events/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::core::SurfaceDrawEvent
#ifndef BT_CORE_SURFACE_DRAW_EVENT_HPP
#include "../../../../public/bt/core/render/events/SurfaceDrawEvent.hpp"
#endif // !BT_CORE_SURFACE_DRAW_EVENT_HPP

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
              mSurfaceDrawEventSent( false )
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager created", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG
        }

        GLRenderManager::~GLRenderManager() BT_NOEXCEPT
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager destructed", static_cast<unsigned char>(bt_ELogLevel::Info) );
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

        bool GLRenderManager::onSurfaceReady()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print(u8"GLRenderManager::onSurfaceReady", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            // Update Surface-Color.
            glClearColor( mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a );

            // Notify
            bt_sptr<ecs_IEvent> loadEvent = bt_Memory::StaticCast<ecs_IEvent, bt_LoadEvent>( bt_Shared<bt_LoadEvent>(mSurfaceReady) );
            if (ecs_Event::Send(loadEvent, false, static_cast<ecs_uint8_t>(bt_EThreadTypes::Render) ) < 0 )
                return false;

            // Send SurfaceDrawEvent
            queueSurfaceDrawEvent();

            // Set Surface-Ready flag.
            mSurfaceReady = true;

            // OK
            return true;
        }

        void GLRenderManager::onSurfaceDraw( const bt_real_t elapsedTime )
        {
            // Clear Surface.
            glClear( GL_COLOR_BUFFER_BIT );

            // Update Render-Thread Events.
            ecs_Events::Update( static_cast<ecs_uint8_t>(bt_EThreadTypes::Render) );
        }

        // ===========================================================
        // bt::core::RenderManager
        // ===========================================================

        bool GLRenderManager::onStart()
        {
            // Send SurfaceDrawEvent
            queueSurfaceDrawEvent();

            return RenderManager::onStart();
        }

        bool GLRenderManager::onResume()
        {
            // Send SurfaceDrawEvent
            queueSurfaceDrawEvent();

            return RenderManager::onResume();
        }

        void GLRenderManager::onPause()
        {
            flushSurfaceDrawEvents();

            RenderManager::onPause();
        }

        void GLRenderManager::onStop()
        {
            flushSurfaceDrawEvents();

            RenderManager::onStop();
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        void GLRenderManager::queueSurfaceDrawEvent()
        {
            if ( !mSurfaceDrawEventSent )
            {
                bt_sptr<ecs_IEvent> surfaceDrawEvent = bt_Memory::StaticCast<ecs_IEvent, bt_SurfaceDrawEvent>( bt_Shared<bt_SurfaceDrawEvent>(static_cast<ecs_uint8_t>( bt_EThreadTypes::Render )) );
                ecs_Events::queueEvent(surfaceDrawEvent, static_cast<ecs_uint8_t>(bt_EThreadTypes::Render) );
                mSurfaceDrawEventSent = true;
            }
        }

        void GLRenderManager::flushSurfaceDrawEvents()
        {
            if ( mSurfaceDrawEventSent )
                ecs_Events::FlushEvents(static_cast<ecs_TypeID>(bt_EEventTypes::SurfaceDraw), static_cast<unsigned char>(bt_EThreadTypes::Render) );
        }

        // -----------------------------------------------------------

    } /// bt::gl

} /// bt

// -----------------------------------------------------------
