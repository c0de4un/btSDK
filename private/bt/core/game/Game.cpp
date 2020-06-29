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
#ifndef BT_CORE_GAME_HPP
#include "../../../public/bt/core/game/Game.hpp"
#endif // !BT_CORE_GAME_HPP

// Include bt::systems
#ifndef BT_CFG_SYSTEMS_HPP
#include "../../../public/bt/cfg/bt_systems.hpp"
#endif // !BT_CFG_SYSTEMS_HPP

// Include bt::threads
#ifndef BT_CFG_THREADS_HPP
#include "../../../public/bt/cfg/bt_threads.hpp"
#endif // !BT_CFG_THREADS_HPP

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "../../../public/bt/ecs/event/IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include ecs::EventsManager
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// Include bt::core::LoadEvent
#ifndef BT_CORE_LOAD_EVENT_HPP
#include "../../../public/bt/core/assets/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::core::GraphicsManager
#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#include "../../../public/bt/core/graphics/GraphicsManager.hpp"
#endif // !BT_CORE_GRAPHICS_MANAGER_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../public/bt/cfg/bt_string.hpp"
#endif

// Get Application
#ifndef BT_CORE_APPLICATION_HPP
#include "../../../public/bt/core/app/Application.hpp"
#endif // !BT_CORE_APPLICATION_HPP

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

#endif // DEBUG

// ===========================================================
// bt::core::Game
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        bt_AsyncStorage<bt_sptr<Game>> Game::mInstanceHolder;

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        Game::Game()
            : System( static_cast<bt_uint8_t>( bt_SystemTypes::GAME ) )
        {
        }

        Game::~Game() = default;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        BT_API bt_sptr<Game> Game::getInstance() noexcept
        { return mInstanceHolder.getItem(); }

        // ===========================================================
        // METHODS
        // ===========================================================

        BT_API void Game::Initialize( bt_sptr<Game>& pInstance )
        {
            if ( getInstance() == nullptr )
            {
                mInstanceHolder.setItem( pInstance );
                bt_sptr<ecs_ISystem> system = bt_Memory::StaticCast<ecs_ISystem, bt_Game>( pInstance );
                ecs_Systems::registerSystem( system );
            }
        }

        BT_API void Game::Terminate()
        {
            bt_sptr<bt_Game> gameInstance( getInstance() );
            if ( gameInstance != nullptr )
            {
                gameInstance->Stop();
                ecs_Systems::unregisterSystem( gameInstance->getTypeID() );
                mInstanceHolder.setItem( bt_sptr<bt_Game>(nullptr) );
            }
        }

        bool Game::onLoad( const bool pRestored )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onLoad", bt_ELogLevel::Info );
#endif // DEBUG

            return true;
        }

        // ===========================================================
        // ecs::System
        // ===========================================================

        char Game::OnEvent( ecs_sptr<ecs_IEvent> pEvent, const bool pAsync, const unsigned char pThread )
        {
            if ( !isStarted() || isPaused() )
                return 0;

            // Handle Event.
            switch( static_cast<bt_EEventTypes>(pEvent->getTypeID( )) )
            {
                case bt_EEventTypes::AssetsLoading:
                    return onLoad( bt_Memory::StaticCast<bt_LoadEvent, ecs_IEvent>( pEvent )->mReload ) ? 1 : 0;

                default:
                    break;
            }

            return 0;
        }

        void Game::onEventError( ecs_sptr<ecs_IEvent> pEvent, const std::exception& pException, const bool pAsync, const unsigned char pThread )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_String logMsg = u8"Game::onEventError: ERROR=";
            logMsg += pException.what();
            logMsg += u8" ; Event-Type=";
            logMsg += bt_StringUtil::toString<ecs_TypeID>( pEvent->getTypeID() );
            logMsg += u8" ; Event-ID=";
            logMsg += bt_StringUtil::toString<ecs_TypeID>( pEvent->getID() );
            bt_Log::Print( logMsg.c_str(), static_cast<unsigned char>( bt_ELogLevel::Error ) );
#endif // DEBUG

            // Notify Application
            bt_sptr<bt_App> gameApp( bt_App::getInstance() );
            if ( gameApp != nullptr )
                gameApp->onEventError( pEvent, pException, pAsync, pThread );
        }

        bool Game::onStart()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onStart", bt_ELogLevel::Info );
#endif // DEBUG

            // Subscribe
            Subscribe<bt_EEventTypes>( this, { bt_EEventTypes::AssetsLoading } );

            return true;
        }

        bool Game::onResume()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            // Subscribe
            Subscribe<bt_EEventTypes>( this, { bt_EEventTypes::AssetsLoading } );

            return true;
        }

        void Game::onPause()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            // Unsubscribe
            Unsubscribe<bt_EEventTypes>( this, { bt_EEventTypes::AssetsLoading } );
        }

        void Game::onStop()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Unsubscribe
            Unsubscribe<bt_EEventTypes>( this, { bt_EEventTypes::AssetsLoading } );
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------