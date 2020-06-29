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
#ifndef BT_CORE_APPLICATION_HPP
#include "../../../public/bt/core/app/Application.hpp"
#endif // !BT_CORE_APPLICATION_HPP

// Include bt::systems
#ifndef BT_CFG_SYSTEMS_HPP
#include "../../../public/bt/cfg/bt_systems.hpp"
#endif // !BT_CFG_SYSTEMS_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// Include bt::events
#ifndef BT_CFG_EVENTS_HPP
#include "../../../public/bt/cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

// Include bt::core::Graphics
#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#include "../../../public/bt/core/graphics/GraphicsManager.hpp"
#endif // !BT_CORE_GRAPHICS_MANAGER_HPP

// Include bt::core::Engine
#ifndef BT_CORE_ENGINE_HPP
#include "../../../public/bt/core/engine/Engine.hpp"
#endif // !BT_CORE_ENGINE_HPP

// Include bt::core::Game
#ifndef BT_CORE_GAME_HPP
#include "../../../public/bt/core/game/Game.hpp"
#endif // !BT_CORE_GAME_HPP

// Include ecs
#ifndef BT_ECS_HPP
#include "../../../public/bt/ecs/ecs.hpp"
#endif // !BT_ECS_HPP

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../public/bt/cfg/bt_string.hpp"
#endif

#endif // DEBUG

// ===========================================================
// bt::core::Application
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        bt_AsyncStorage<bt_sptr<Application>> Application::mInstanceStorage;

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        Application::Application(const bt_AppParams& appParams)
            : System( static_cast<ecs_TypeID>( bt_SystemTypes::APPLICATION ) ),
            mParams( appParams )
        {
        }

        Application::~Application() = default;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        BT_API bt_sptr<Application> Application::getInstance() noexcept
        { return mInstanceStorage.getItem(); }

        BT_API bool Application::hasInstance() BT_NOEXCEPT
        { return getInstance() != nullptr; }

        // ===========================================================
        // METHODS
        // ===========================================================

        void Application::onTerminate() BT_NOEXCEPT
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::onTerminate", bt_ELogLevel::Info );
#endif // DEBUG

            // Terminate Game
            bt_Game::Terminate();

            // Terminate Engine
            bt_Engine::Terminate();

            // Terminate Graphics
            bt_Graphics::Terminate();
        }

        BT_API void Application::Initialize( bt_sptr<Application>& pInstance )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::Initialize", bt_ELogLevel::Info );
#endif // DEBUG

            if ( !hasInstance() )
            {
                // Initialize ECS
                ecs_Engine::Initialize();

                // Initialize Application
                ecs_sptr<ecs_ISystem> system = bt_Memory::StaticCast<ecs_ISystem, bt_App>( pInstance );
                ecs_Systems::registerSystem( system );

                mInstanceStorage.setItem( pInstance );
            }
        }

        BT_API void Application::Terminate()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::Terminate", bt_ELogLevel::Info );
#endif // DEBUG

            // Terminate Application
            bt_sptr<bt_App> instance = getInstance();
            if ( instance != nullptr )
            {
                // Stop
                instance->Stop();

                // Terminate
                instance->onTerminate();

                // Self-Remove
                ecs_Systems::unregisterSystem( instance->getTypeID() );

                // Reset Instance
                mInstanceStorage.setItem( bt_sptr<bt_App>(nullptr) );
            }

            // Terminate ECS
            ecs_Engine::Terminate();

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            // Terminate Log
            bt_Log::Terminate();
#endif // DEBUG
        }

        // ===========================================================
        // ISystem
        // ===========================================================

        bool Application::onStart()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::onStart", bt_ELogLevel::Info );
#endif // DEBUG

            // Get Graphics
            bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();

            // Get Engine
            bt_sptr<bt_Engine> engine = bt_Engine::getInstance();

            // Get Game
            bt_sptr<bt_Game> game = bt_Game::getInstance();

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( graphics != nullptr && "Application::onStart - Graphics must be initialized before starting." );
            bt_assert( engine != nullptr && "Application::onStart - Engine must be initialized before starting." );
            bt_assert( game != nullptr && "Application::onStart - Game must be initialized before starting." );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Start Game
                if ( !game->Start() ) // Model
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onStart - failed to start Game";
                    bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
                    return false;
                }
#else // !DEBUG
                    return false;
#endif // DEBUG

                // Start Engine
                if ( !engine->Start() ) // Controller
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onStart - failed to start Engine";
                    bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
                    return false;
                }
#else // !DEBUG
                    return false;
#endif // DEBUG

                // Start Graphics
                if ( !graphics->Start() ) // View
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onStart - failed to start Graphics";
                    bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
                    return false;
                }
#else // !DEBUG
                    return false;
#endif // DEBUG

                return System::onStart();
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg = u8"Application::onStart - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // !DEBUG

                // Stop
                Stop();
            }

            return false;
        }

        bool Application::onResume()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            // Get Graphics
            bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();

            // Get Engine
            bt_sptr<bt_Engine> engine = bt_Engine::getInstance();

            // Get Game
            bt_sptr<bt_Game> game = bt_Game::getInstance();

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                    bt_assert( graphics != nullptr && "Application::onResume - Graphics must be initialized before starting." );
                    bt_assert( engine != nullptr && "Application::onResume - Engine must be initialized before starting." );
                    bt_assert( game != nullptr && "Application::onResume - Game must be initialized before starting." );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Resume Graphics
                if ( !graphics->Start() ) // View
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onResume - failed to resume Graphics";
                    bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
                    return false;
                }
#else // !DEBUG
                return false;
#endif // DEBUG

                // Resume Engine
                if ( !engine->Start() ) // Controller
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onResume - failed to resume Engine";
                    bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
                    return false;
                }
#else // !DEBUG
                return false;
#endif // DEBUG

                // Resume Game
                if ( !game->Start() ) // Model
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                {
                    bt_String logMsg = u8"Application::onResume - failed to resume Game";
                    bt_Log::Print( logMsg.c_str(), static_cast<bt_uint8_t>(bt_ELogLevel::Error) );
                    return false;
                }
#else // !DEBUG
                return false;
#endif // DEBUG

                return System::onResume();
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg = u8"Application::onResume - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // !DEBUG

                // Stop
                Stop();
            }

            return false;
        }

        void Application::onPause()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            // Get Graphics
            bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();

            // Get Engine
            bt_sptr<bt_Engine> engine = bt_Engine::getInstance();

            // Get Game
            bt_sptr<bt_Game> game = bt_Game::getInstance();

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( graphics != nullptr && "Application::onPause - Graphics must be initialized before starting." );
            bt_assert( engine != nullptr && "Application::onPause - Engine must be initialized before starting." );
            bt_assert( game != nullptr && "Application::onPause - Game must be initialized before starting." );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Pause Game
                game->Pause(); // Model

                // Pause Engine
                engine->Pause(); // Controller

                // Pause Graphics
                graphics->Pause(); // View

                System::onPause();
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg = u8"Application::onPause - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // !DEBUG

                // Stop
                Stop();
            }
        }

        void Application::onStop()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Application::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Get Graphics
            bt_sptr<bt_Graphics> graphics = bt_Graphics::getInstance();

            // Get Engine
            bt_sptr<bt_Engine> engine = bt_Engine::getInstance();

            // Get Game
            bt_sptr<bt_Game> game = bt_Game::getInstance();

            // Guarded-Block
            try
            {
                // Stop Game
                if ( game != nullptr )
                    game->Pause(); // Model

                // Stop Engine
                if ( engine != nullptr )
                    engine->Pause(); // Controller

                // Stop Graphics
                if ( graphics != nullptr )
                    graphics->Pause(); // View

                System::onStop();

                // Terminate Application
                Terminate();
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg = u8"Application::onStop - ERROR: ";
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // !DEBUG
            }
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
