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
#ifndef BT_CORE_ARCADE_ENGINE_HPP
#include "../../../../public/bt/core/engine/ArcadeEngine.hpp"
#endif // !BT_CORE_ARCADE_ENGINE_HPP

// Include bt::core::Exception
#ifndef BT_CORE_EXCEPTION_HPP
#include "../../../../public/bt/core/metrics/Exception.hpp"
#endif // !BT_CORE_EXCEPTION_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../../public/bt/cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "../../../../public/bt/ecs/event/IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include bt::core::LoadEvent
#ifndef BT_CORE_LOAD_EVENT_HPP
#include "../../../../public/bt/core/assets/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::threads
#ifndef BT_CFG_THREADS_HPP
#include "../../../../public/bt/cfg/bt_threads.hpp"
#endif // !BT_CFG_THREADS_HPP

// Include bt::core::AssetsManager

// Include bt::core::InputManager

// Include bt::core::TasksManager

// Include bt::core::ExtensionsManager

// Include bt::core::AudioManager

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

#endif
// DEBUG

// ===========================================================
// bt::core::ArcadeEngine
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        ArcadeEngine::ArcadeEngine()
            : Engine()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"ArcadeEngine construct", bt_ELogLevel::Info );
#endif // DEBUG
        }

        ArcadeEngine::~ArcadeEngine()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"ArcadeEngine destruct", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // bt::core::Engine
        // ===========================================================

        bool ArcadeEngine::onLoadAssets( const bool pReloading )
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onLoadAssets", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Send LoadEvent for all Assets
                bt_sptr<ecs_IEvent> event( bt_SharedCast<ecs_IEvent, bt_LoadEvent>(bt_Shared<bt_LoadEvent>( pReloading )) );
                if ( ecs_Event::Send(event, false, static_cast<ecs_TypeID>( bt_EThreadTypes::Render )) < 0 )
                    return false;
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onLoadAssets - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return Engine::onLoadAssets();
        }

        void ArcadeEngine::onDraw()
        {
            // Guarded-Block
            try
            {
                // @TODO Update Render-Thread Events
                // @TODO Update Render-Thread Tasks
                // @TODO Send Draw3D Event
                // @TODO Send Draw2D Event
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onDraw - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }
        }

        bool ArcadeEngine::onStart()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onStart", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onStart - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return Engine::onStart();
        }

        bool ArcadeEngine::onResume()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onResume - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return Engine::onResume();
        }

        void ArcadeEngine::onPause()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onPause - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            Engine::onPause();
        }

        void ArcadeEngine::onStop()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"ArcadeEngine::onStop - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            Engine::onStop();
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
