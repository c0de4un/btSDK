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
#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#include "../../../../public/bt/core/graphics/GraphicsManager.hpp"
#endif // !BT_CORE_GRAPHICS_MANAGER_HPP

// Include bt::SystemTypes
#ifndef BT_CFG_SYSTEMS_HPP
#include "../../../../public/bt/cfg/bt_systems.hpp"
#endif // !BT_CFG_SYSTEMS_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// Include bt::core::IGraphicsListener
#ifndef BT_CORE_I_GRAPHICS_LISTENER_HXX
#include "../../../../public/bt/core/graphics/IGraphicsListener.hxx"
#endif // !BT_CORE_I_GRAPHICS_LISTENER_HXX

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../public/bt/cfg/bt_string.hpp"
#endif

// Include bt::core::RenderManager
#ifndef BT_CORE_RENDER_MANAGER_HPP
#include "../../../public/bt/core/render/RenderManager.hpp"
#endif // !BT_CORE_RENDER_MANAGER_HPP

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
// bt::core::GraphicsManager
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        AsyncStorage<bt_sptr<GraphicsManager>> GraphicsManager::mInstanceStorage;

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        GraphicsManager::GraphicsManager( const GraphicsSettings& pSettings )
            : System( static_cast<const ecs_TypeID>(bt_SystemTypes::GRAPHICS) ),
            mSettings( pSettings )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"GraphicsManager constructor", bt_ELogLevel::Info );
#endif // DEBUG
        }

        GraphicsManager::~GraphicsManager()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"GraphicsManager destructor", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        GraphicsSettings GraphicsManager::getSettings() const BT_NOEXCEPT
        { return mSettings; }

        bt_sptr<GraphicsManager> GraphicsManager::getInstance() BT_NOEXCEPT
        { return mInstanceStorage.getItem(); }

        // ===========================================================
        // METHODS
        // ===========================================================

        void GraphicsManager::onTerminate()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"GraphicsManager::onTerminate", bt_ELogLevel::Info );
#endif // DEBUG

            // Terminate RenderManager
            bt_RenderManager::Terminate();
        }

        void GraphicsManager::Initialize( bt_sptr<GraphicsManager> pInstance )
        {
            if ( mInstanceStorage.getItem() == nullptr )
            {
                // Create & Register Graphics-System
                bt_sptr<bt_Graphics> graphicsInstance = bt_Memory::MoveShared(pInstance);
                bt_sptr<ecs_ISystem> system( bt_SharedCast<ecs_ISystem, bt_Graphics>( graphicsInstance ) );
                ecs_Systems::registerSystem( system );
                mInstanceStorage.setItem( graphicsInstance );
            }
        }

        void GraphicsManager::Terminate()
        {
            bt_sptr<bt_Graphics> graphicsInstance( getInstance() );
            if ( graphicsInstance != nullptr )
            {
                // Notify
                graphicsInstance->onTerminate();

                // Release instance.
                ecs_Systems::unregisterSystem( graphicsInstance->getTypeID() );
                mInstanceStorage.setItem( bt_sptr<bt_Graphics>(nullptr) );
            }
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
