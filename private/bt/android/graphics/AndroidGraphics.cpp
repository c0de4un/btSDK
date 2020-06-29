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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_ANDROID_GRAPHICS_HPP
#include "../../../../public/bt/android/graphics/AndroidGraphics.hpp"
#endif // !BT_ANDROID_GRAPHICS_HPP

// Include bt::gl::GLRenderManager
#ifndef BT_GL_RENDER_MANAGER_HPP
#include "../../../../public/bt/gl/render/GLRendererManager.hpp"
#endif // !BT_GL_RENDER_MANAGER_HPP

// DEBUG
#if defined( DEBUG ) || defined( BT_DEBUG )

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../../public/bt/cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

#endif
// DEBUG

// ===========================================================
// bt::android::AndroidGraphics
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        AndroidGraphics::AndroidGraphics( const bt_GraphicsSettings& pSettings )
            : GraphicsManager( pSettings ),
              mGLRenderer( nullptr )
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics created", bt_ELogLevel::Info );
#endif // DEBUG
        }

        AndroidGraphics::~AndroidGraphics()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics destroyed", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // IGLSurfaceListener
        // ===========================================================

        bool AndroidGraphics::onGLSurfaceReady( const bt_GraphicsSettings* const pSettings )
        {
            // Update Settings.
            mSettings = *pSettings;

            // Get GLRenderManager
            mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );

#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_assert( mGLRenderer != nullptr && "AndroidGraphics::onGLSurfaceReady - GLRenderManager not set." );
#endif // DEBUG

            // Notify GLRenderManager
            return mGLRenderer->onGLSurfaceReady(pSettings);
        }

        void AndroidGraphics::onGLSurfaceDraw()
        {
            // Cancel if not Started or Paused.
            if ( !isStarted() || isPaused() || mGLRenderer == nullptr )
                return;

            // Notify GLRenderManager
            mGLRenderer->onGLSurfaceDraw();
        }

        // ===========================================================
        // bt::core::GraphicsManager
        // ===========================================================

        bool AndroidGraphics::onStart()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics::onStart", static_cast<bt_uint8_t>( bt_ELogLevel::Info ) );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Start GLRenderManager
                mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );
                if ( mGLRenderer != nullptr && !mGLRenderer->Start() )
                {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                    bt_Log::Print( u8"AndroidGraphics::onStart - failed to Start GLRenderManager", bt_ELogLevel::Error );
#endif // DEBUG

                    return false;
                }

                return GraphicsManager::onStart();
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg = u8"AndroidGraphics::onStart - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG
            }

            return false;
        }

        bool AndroidGraphics::onResume()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Resume GLRenderManager
                mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );
                if ( mGLRenderer != nullptr && !mGLRenderer->Start() )
                {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                    bt_Log::Print( u8"AndroidGraphics::onStart - failed to Resume GLRenderManager", bt_ELogLevel::Error );
#endif // DEBUG

                    return false;
                }

                // Get GLRenderManager
                mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );

                return GraphicsManager::onResume();
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg = u8"AndroidGraphics::onResume - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG
            }

            return false;
        }

        void AndroidGraphics::onPause()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Pause GLRenderManager
                mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );
                if ( mGLRenderer != nullptr )
                    mGLRenderer->Pause();

                // Release GLRenderManager
                mGLRenderer = nullptr;

                GraphicsManager::onPause();
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg = u8"AndroidGraphics::onPause - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG
            }
        }

        void AndroidGraphics::onStop()
        {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidGraphics::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Stop GLRenderManager
                mGLRenderer = bt_SharedCast<bt_GLRenderManager, bt_RenderManager>( bt_RenderManager::getInstance() );
                if ( mGLRenderer != nullptr )
                    mGLRenderer->Stop();

                // Release GLRenderManager
                mGLRenderer = nullptr;

                GraphicsManager::onStop();
            }
            catch( const std::exception& pException )
            {
#if defined( DEBUG ) || defined( BT_DEBUG ) // DEBUG
                bt_String logMsg = u8"AndroidGraphics::onStop - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG
            }
        }

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

// -----------------------------------------------------------
