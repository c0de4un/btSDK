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

// DEBUG
#if defined( DEBUG ) || defined(BT_DEBUG)

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
        }

        ArcadeEngine::~ArcadeEngine() = default;

        // ===========================================================
        // bt::core::Engine
        // ===========================================================

        bool ArcadeEngine::onStart()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onStart", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            return Engine::onStart();
        }

        bool ArcadeEngine::onResume()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onResume", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            return Engine::onResume();
        }

        void ArcadeEngine::onPause()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onPause", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            Engine::onPause();
        }

        void ArcadeEngine::onStop()
        {
#if defined( DEBUG ) || defined(BT_DEBUG) // DEBUG
            bt_Log::Print(u8"ArcadeEngine::onStop", static_cast<unsigned char>(bt_ELogLevel::Info) );
#endif // DEBUG

            Engine::onStop();
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
