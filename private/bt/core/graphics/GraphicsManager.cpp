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

// Include bt::core::IGraphicsListener
#ifndef BT_CORE_I_GRAPHICS_LISTENER_HXX
#include "../../../../public/bt/core/graphics/IGraphicsListener.hxx"
#endif // !BT_CORE_I_GRAPHICS_LISTENER_HXX

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

        bt_sptr<GraphicsManager> GraphicsManager::mInstance(nullptr);

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        GraphicsManager::GraphicsManager( const GraphicsSettings& pSettings )
            : System( static_cast<const ecs_TypeID>(bt_SystemTypes::GRAPHICS) ),
            mSettings( pSettings ),
              mGraphicsListeners()
        {
        }

        GraphicsManager::~GraphicsManager()
        {
            this->Stop();
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        GraphicsSettings GraphicsManager::getSettings() const BT_NOEXCEPT
        { return mSettings; }

        bt_sptr<GraphicsManager> GraphicsManager::getInstance() BT_NOEXCEPT
        { return mInstance; }



        // ===========================================================
        // ecs::System
        // ===========================================================

        bool GraphicsManager::onStart()
        {
            return System::onStart();
        }

        bool GraphicsManager::onResume()
        {
            return System::onResume();
        }

        void GraphicsManager::onPause()
        {
            System::onPause();
        }

        void GraphicsManager::onStop()
        {
            System::onStop();
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        bool GraphicsManager::onSurfaceReady()
        {
            bt_size_t listenersCount = mGraphicsListeners.Count();

            for( bt_size_t i = 0; i < listenersCount; i++)
            {
                if ( mGraphicsListeners.Count() < i || !mGraphicsListeners[i]->onSurfaceReady() )
                    return false;
            }

            return true;
        }

        void GraphicsManager::onSurfaceDraw( const bt_real_t elapsedTime )
        {
            bt_size_t listenersCount = mGraphicsListeners.Count();

            for( bt_size_t i = 0; i < listenersCount; i++)
            {
                if ( mGraphicsListeners.Count() < i )
                    break;

                mGraphicsListeners[i]->onSurfaceDraw( elapsedTime );
            }
        }

        void GraphicsManager::registerGraphicsListener( graphics_listener pListener )
        {
            if ( !mGraphicsListeners.Find(pListener, nullptr) )
                mGraphicsListeners.Push( pListener );
        }

        void GraphicsManager::unregisterGraphicsListener( graphics_listener& pListener )
        { mGraphicsListeners.Erase( pListener, true ); }

        void GraphicsManager::Initialize( bt_sptr<GraphicsManager> pInstance )
        {
            if ( mInstance != nullptr )
                return;

            mInstance = bt_Memory::MoveShared(pInstance); //std::move(pInstance);
        }

        void GraphicsManager::Terminate()
        {
            mInstance = nullptr;
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
