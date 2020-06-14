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
#include "../../../public/bt/core/render/events/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::core::GraphicsManager
#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#include "../../../public/bt/core/graphics/GraphicsManager.hpp"
#endif // !BT_CORE_GRAPHICS_MANAGER_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG

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

        bt_sptr<Game> Game::mInstance(nullptr);

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

        // ===========================================================
        // METHODS
        // ===========================================================

        ECS_API void Game::SubscribeGame( Game* const pInstance, const ecs_vec<bt_EEventTypes>& pEvents )
        {
            bt_vector<ecs_TypeID> types;
            types.reserve( pEvents.size() );

            for( const bt_EEventTypes& eventType : pEvents )
            { types.push_back( static_cast<ecs_TypeID>(eventType) ); }

            ecs_System::SubscribeSystem( static_cast<ecs_System*>(pInstance), types );
        }

        ECS_API void Game::UnsubscribeGame( Game* const pInstance, const ecs_vec<bt_EEventTypes>& pEvents )
        {
            bt_vector<ecs_TypeID> types;
            types.reserve( pEvents.size() );

            for( const bt_EEventTypes& eventType : pEvents )
            { types.push_back( static_cast<ecs_TypeID>(eventType) ); }

            ecs_System::UnsubscribeSystem( static_cast<ecs_System*>(pInstance), types );
        }

        BT_API void Game::Initialize( bt_sptr<Game>& pInstance )
        {
            if ( mInstance == nullptr )
            {
                mInstance = pInstance;
                bt_sptr<ecs_ISystem> system = bt_Memory::StaticCast<ecs_ISystem, bt_Game>( mInstance );
                ecs_Systems::registerSystem( system );
            }
        }

        BT_API void Game::Terminate()
        {
            if ( mInstance != nullptr )
            {
                ecs_Systems::unregisterSystem( mInstance->getTypeID() );
                mInstance = nullptr;
            }
        }

        void Game::onDraw()
        {
        }

        bool Game::onLoad( const bool pRestored )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Game::onLoad", static_cast<unsigned char>( bt_ELogLevel::Info ) );
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

                case bt_EEventTypes::SurfaceDraw:
                    onDraw();
                    break;

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

            // Stop
            bt_Graphics::Terminate();
        }

        bool Game::onStart()
        {
            // Subscribe
            SubscribeGame( this, { bt_EEventTypes::AssetsLoading, bt_EEventTypes::SurfaceDraw, bt_EEventTypes::LogicUpdate } );

            return true;
        }

        bool Game::onResume()
        {
            // Subscribe
            SubscribeGame( this, { bt_EEventTypes::AssetsLoading, bt_EEventTypes::SurfaceDraw, bt_EEventTypes::LogicUpdate } );

            return true;
        }

        void Game::onPause()
        {
            // Unsubscribe
            UnsubscribeGame( this, { bt_EEventTypes::AssetsLoading, bt_EEventTypes::SurfaceDraw, bt_EEventTypes::LogicUpdate } );
        }

        void Game::onStop()
        {
            // Unsubscribe
            UnsubscribeGame( this, { bt_EEventTypes::AssetsLoading, bt_EEventTypes::SurfaceDraw, bt_EEventTypes::LogicUpdate } );
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------