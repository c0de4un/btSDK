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

#ifndef BT_CFG_EVENTS_HPP
#define BT_CFG_EVENTS_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../ecs/types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        BT_ENUM_TYPE EEventTypes : bt_uint8_t
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_ENUM

            // ===========================================================
            // CONSTANTS
            // ===========================================================

            /** Min. Value **/
            MIN = 0,

            /** Rendering Surface is ready, Assets can be loaded/restored. **/
            AssetsLoading = 1,

            /** Surface-Draw. Called from Render Threads-Type every frame. **/
            SurfaceDraw = 2,

            /** Surface-Ready. Called from Render-Thread when Surface created/changed/restored. **/
            SurfaceReady = 3,

            /** Logic State Update. **/
            LogicUpdate = 4,

            /** Physics State Update. **/
            PhysicsUpdate = 5,

            /** Max. value. User for override (extend). **/
            MAX = 99

            // -----------------------------------------------------------

        };

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_EEventTypes = bt::core::EEventTypes;

// -----------------------------------------------------------

#endif // !BT_CFG_EVENTS_HPP
