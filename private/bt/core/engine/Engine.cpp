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
#ifndef BT_CORE_ENGINE_HPP
#include "../../../../public/bt/core/engine/Engine.hpp"
#endif // !BT_CORE_ENGINE_HPP

// Include bt::SystemTypes
#ifndef BT_CFG_SYSTEMS_HPP
#include "../../../../public/bt/cfg/bt_systems.hpp"
#endif // !BT_CFG_SYSTEMS_HPP

// Include bt::Events
#ifndef BT_CFG_EVENTS_HPP
#include "../../../../public/bt/cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

// Include bt::threads
#ifndef BT_CFG_THREADS_HPP
#include "../../../../public/bt/cfg/bt_threads.hpp"
#endif // !BT_CFG_THREADS_HPP

// Include bt::core::RenderManager
#ifndef BT_CORE_RENDER_MANAGER_HPP
#include "../../../../public/bt/core/render/RenderManager.hpp"
#endif // !BT_CORE_RENDER_MANAGER_HPP

// Include bt::core::AssetsManager

// Include bt::core::InputManager

// Include bt::core::TasksManager

// Include bt::core::ExtensionsManager

// Include bt::core::AudioManager

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../../public/bt/cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

// Include bt::core::Exception
#ifndef BT_CORE_EXCEPTION_HPP
#include "../../../../public/bt/core/metrics/Exception.hpp"
#endif // !BT_CORE_EXCEPTION_HPP

// Include ecs::IEvent
#ifndef ECS_I_EVENT_HXX
#include "../../../../public/bt/ecs/event/IEvent.hxx"
#endif // !ECS_I_EVENT_HXX

// Include bt::core::Application
#ifndef BT_CORE_APPLICATION_HPP
#include "../../../../public/bt/core/app/Application.hpp"
#endif // !BT_CORE_APPLICATION_HPP

// Include ecs::EventsManager
#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../../public/bt/ecs/event/EventsManager.hpp"
#endif // !ECS_EVENTS_MANAGER_HPP

// Include bt::core::LoadEvent
#ifndef BT_CORE_LOAD_EVENT_HPP
#include "../../../../public/bt/core/assets/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../../public/bt/cfg/bt_log.hpp"
#include "../../../../public/bt/core/render/events/SurfaceReadyEvent.hpp"

#endif // !BT_CFG_LOG_HPP

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

#endif
// DEBUG

// ===========================================================
//
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        bt_AsyncStorage<bt_sptr<Engine>> Engine::mInstanceHolder;

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        Engine::Engine()
            : System( static_cast<const ecs_TypeID>(bt_SystemTypes::ENGINE) )
        {
        }

        Engine::~Engine()
        {
            this->Stop();
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        bt_sptr<Engine> Engine::getInstance() BT_NOEXCEPT
        { return mInstanceHolder.getItem(); }

        // ===========================================================
        // METHODS
        // ===========================================================

        bool Engine::onLoadAssets( const bool pReloading )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Engine::onLoadAssets", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Send LoadEvent
                bt_sptr<bt_LoadEvent> loadEvent( bt_Shared<bt_LoadEvent>(pReloading) );
                loadEvent->setFlag( bt_LoadEvent::GPU_ASSETS_FLAG, true ); // Load GPU-Related Assets
                loadEvent->setFlag( bt_LoadEvent::AUDIO_ASSETS_FLAG, true ); // Load Audio Assets
                bt_sptr<ecs_IEvent> event( bt_SharedCast<ecs_IEvent, bt_LoadEvent>(loadEvent) );
                if ( ecs_Event::Send( event, false, static_cast<ecs_TypeID>(bt_EThreadTypes::Render) ) < 0 )
                {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                    bt_Log::Print( u8"Engine::onLoadAssets - failed", bt_ELogLevel::Warning );
#endif // DEBUG

                    return false;
                }
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"Engine::onLoadAssets - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return true;
        }

        void Engine::onDraw()
        {
            // Update/Send Render-Thread Events
            ecs_Events::Update( static_cast<ecs_TypeID>(bt_EThreadTypes::Render) );

            // @TODO Update Render-Thread Tasks

            // @TODO Draw 3D

            // @TODO Draw 2D
        }

        // ===========================================================
        // IEventListener
        // ===========================================================

        char Engine::OnEvent( ecs_sptr<ecs_IEvent> pEvent, const bool pAsync, const unsigned char pThread )
        {
            // Cancel if not Started or Paused
            if ( !isStarted() || isPaused() )
                return 0;

            // Handle Event
            const auto eventType( static_cast<bt_EEventTypes>(pEvent->getTypeID()) );
            switch( eventType )
            {
                // Render Surface is Created (|| Changed || Restored)
                case bt_EEventTypes::SurfaceReady:
                {
                    bt_sptr<bt_SurfaceReady> surfaceReadyEvent( bt_SharedCast<bt_SurfaceReady, ecs_IEvent>(pEvent) );
                    if ( !onLoadAssets( surfaceReadyEvent->mRestoredSurface ) )
                        throw bt_Exception( "Engine::onLoadAssets - failed to load assets." );
                }

                    break;

                // Render Surface Frame-Draw
                case bt_EEventTypes::SurfaceDraw:
                    onDraw();
                    break;

                default:
                    break;
            }

            return 0;
        }

        void Engine::onEventError( ecs_sptr<ecs_IEvent> pEvent, const std::exception& pException, const bool pAsync, const unsigned char pThread )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_String logMsg( u8"Engine::onEventError - ERROR: " );
            logMsg += pException.what();
            bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

            // Send to Application
            bt_sptr<bt_App> application( bt_App::getInstance() );
            if ( application != nullptr )
                application->onEventError( pEvent, pException, pAsync, pThread );
        }

        // ===========================================================
        // ISystem
        // ===========================================================

        bool Engine::onStart()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Engine::onStart", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Subscribe
                Subscribe<bt_EEventTypes>( this, { bt_EEventTypes::SurfaceDraw, bt_EEventTypes::SurfaceReady } );
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"Engine::onStart - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return System::onStart();
        }

        bool Engine::onResume()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Engine::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"Engine::onResume - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            return System::onResume();
        }

        void Engine::onPause()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Engine::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {

            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"Engine::onPause - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            System::onPause();
        }

        void Engine::onStop()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"Engine::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Guarded-Block
            try
            {
                // Unsubscribe
                Unsubscribe<bt_EEventTypes>( this, { bt_EEventTypes::SurfaceDraw, bt_EEventTypes::SurfaceReady } );
            }
            catch( const std::exception& pException )
            {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_String logMsg( u8"Engine::onStop - ERROR: " );
                logMsg += pException.what();
                bt_Log::Print( logMsg.c_str(), bt_ELogLevel::Error );
#endif // DEBUG

                // Re-throw.
                throw;
            }

            System::onPause();
        }

        void Engine::Initialize( bt_sptr<Engine> pInstance )
        {
            bt_sptr<bt_Engine> instance = getInstance();
            if ( instance == nullptr )
                mInstanceHolder.setItem( bt_Memory::MoveShared(pInstance) ); //std::move(pInstance)
        }

        void Engine::Terminate()
        { mInstanceHolder.setItem( bt_sptr<bt_Engine>(nullptr) ); }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------