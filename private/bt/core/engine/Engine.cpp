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

// Include bt::core::RenderManager

// Include bt::core::AssetsManager

// Include bt::core::InputManager

// Include bt::core::TasksManager

// Include bt::core::ExtensionsManager

// Include bt::core::AudioManager

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

        bt_sptr<Engine> Engine::mInstance(nullptr);

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
        { return mInstance; }

        // ===========================================================
        // METHODS
        // ===========================================================

        bool Engine::onStart()
        {
            return System::onStart();
        }

        bool Engine::onResume()
        {
            return System::onResume();
        }

        void Engine::onPause()
        {
            System::onPause();
        }

        void Engine::onStop()
        {
            System::onPause();
        }

        void Engine::Initialize( bt_sptr<Engine> pInstance )
        {
            if ( mInstance != nullptr )
                return;

            mInstance = bt_Memory::MoveShared(pInstance); //std::move(pInstance);
        }

        void Engine::Terminate()
        {
            mInstance = nullptr;
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------