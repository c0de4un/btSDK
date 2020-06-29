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
#ifndef BT_CORE_LOAD_EVENT_HPP
#include "../../../../public/bt/core/assets/LoadEvent.hpp"
#endif // !BT_CORE_LOAD_EVENT_HPP

// Include bt::events
#ifndef BT_CFG_EVENTS_HPP
#include "../../../../public/bt/cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

// ===========================================================
// bt::core::LoadEvent
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        LoadEvent::LoadEvent( const bool pReloading, ecs_wptr<ecs_IEventInvoker> pCaller )
            : Event( static_cast<const ecs_TypeID>(bt_EEventTypes::AssetsLoading), false, pCaller ),
              mFlags(),
              mReload( pReloading )
        {
            mFlags.reserve( ASSETS_FLAGS );
        }

        LoadEvent::~LoadEvent() = default;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        void LoadEvent::setFlag( const unsigned char flagName, const bool flagValue ) noexcept
        { mFlags[flagName] = flagValue; }

        bool LoadEvent::isGPU() const noexcept
        { return mFlags[GPU_ASSETS_FLAG]; }

        bool LoadEvent::isAudio() const noexcept
        { return mFlags[AUDIO_ASSETS_FLAG]; }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------