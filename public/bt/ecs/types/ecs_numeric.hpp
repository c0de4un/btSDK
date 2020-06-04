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

#ifndef ECS_NUMERIC_HPP
#define ECS_NUMERIC_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::api
#ifndef ECS_API_HPP
#include "ecs_api.hpp"
#endif // !ECS_API_HPP

// Include bt::numeric
#ifndef BT_CFG_NUMERIC_HPP
#include "../../cfg/bt_numeric.hpp"
#endif // !BT_CFG_NUMERIC_HPP

// ===========================================================
// CONFIG
// ===========================================================

// Use btEnigne::NumericsUtil
template <typename T>
using ecs_NumericUtil = bt_NumericsUtil<T>;

using ecs_int8_t = bt_int8_t;
using ecs_uint8_t = bt_uint8_t;
using ecs_int16_t = bt_int16_t;
using ecs_uint16_t = bt_uint16_t;
using ecs_int32_t = bt_int32_t;
using ecs_uint32_t = bt_uint32_t;
using ecs_int64_t = bt_int64_t;
using ecs_uint64_t = bt_uint64_t;
using ecs_float_t = bt_float_t;
using ecs_double_t = bt_double_t;
using ecs_real_t = bt_real_t;
using ecs_size_t = bt_size_t;

using ecs_TypeID = ecs_uint16_t;
static constexpr const ecs_TypeID ECS_INVALID_TYPE_ID = ecs_NumericUtil<ecs_TypeID>::MAX - 1;

using ecs_ObjectID = ecs_uint32_t;
static constexpr const ecs_ObjectID ECS_INVALID_OBJECT_ID = ecs_NumericUtil<ecs_ObjectID>::MAX - 1;

// -----------------------------------------------------------

#endif // !ECS_NUMERIC_HPP
