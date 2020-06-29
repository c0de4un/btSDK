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

#ifndef BT_CFG_SYSTEMS_HPP
#define BT_CFG_SYSTEMS_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "bt_api.hpp"
#endif // !BT_CFG_API_HPP

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../ecs/types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    // -----------------------------------------------------------

        /**
         * @brief
         * SystemTypes - basic Systems Type-IDs.
         * Designed to support extending by other list, with start from this.MAX.
         *
         * @version 0.1
        **/
        BT_ENUM_TYPE BT_API SystemTypes : ecs_TypeID
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_ENUM

            // -----------------------------------------------------------

            MIN = 0,
            ENGINE = 1,
            GRAPHICS = 2,
            RENDER = 3,
            BATCHING = 4,
            PARTICLES = 5,
            AI = 6,
            AUDIO = 7,
            THREAD = 8,
            TASKS = 9,
            INPUT = 10,
            GAME = 11,
            APPLICATION,
            MAX = 99

            // -----------------------------------------------------------

        }; /// bt::core::Systems

    // -----------------------------------------------------------

} /// bt

using bt_SystemTypes = bt::SystemTypes;

// -----------------------------------------------------------

#endif // !BT_CFG_SYSTEMS_HPP
