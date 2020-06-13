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
#include "../../../../public/bt/core/render/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::core::EThreadTypes
#ifndef BT_CFG_THREADS_HPP
#include "../../../../public/bt/cfg/bt_threads.hpp"
#endif // !BT_CFG_THREADS_HPP

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
            mSurfaceReady( false )
        {
        }

        GLRenderManager::~GLRenderManager() BT_NOEXCEPT = default;

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
            // Update Surface-Color.
            glClearColor( mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a );

            // Notify
            bt_sptr<ecs_IEvent> loadEvent = New<bt_LoadEvent>( mSurfaceReady );
            if ( ecs_Event::Send( loadEvent, false, bt_EThreadTypes::Render ) < 0 )
                return false;

            // Set Surface-Ready flag.
            mSurfaceReady = true;

            // OK
            return true;
        }

        void GLRenderManager::onSurfaceDraw( const bt_real_t elapsedTime )
        {
            // Clear Surface.
            glClear( GL_COLOR_BUFFER_BIT );
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        // -----------------------------------------------------------

    } /// bt::gl

} /// bt

// -----------------------------------------------------------
