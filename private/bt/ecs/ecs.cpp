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
#ifndef ECS_HPP
#include "../../../public/bt/ecs/ecs.hpp"
#endif // ECS_HPP

// Include ecs::ComponentsManager
#ifndef ECS_COMPONENTS_MANAGER_HPP
#include "../../../public/bt/ecs/component/ComponentsManager.hpp"
#endif // !ECS_COMPONENTS_MANAGER_HPP

// Include ecs::EventsManager
//#ifndef ECS_EVENTS_MANAGER_HPP
#include "../../../public/bt/ecs/event/EventsManager.hpp"
//#endif // !ECS_EVENTS_MANAGER_HPP

// Include ecs::EntitiesManager
#ifndef ECS_ENTITIES_MANAGER_HPP
#include "../../../public/bt/ecs/entity/EntitiesManager.hpp"
#endif // !ECS_ENTITIES_MANAGER_HPP

// Include ecs::SystemsManager
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// DEBUG
#if defined( ECS_DEBUG )

// Include ecs::log
#ifndef ECS_LOG_HPP
#include "../../../public/bt/ecs/types/ecs_log.hpp"
#endif // !ECS_LOG_HPP

#endif
// DEBUG

// ===========================================================
// ecs::ECSEngine
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    ECSEngine::ECSEngine() = default;

    ECSEngine::~ECSEngine() = default;

    // ===========================================================
    // METHODS
    // ===========================================================

    void ECSEngine::Initialize()
    {
#if defined( ECS_DEBUG ) // DEBUG
        ecs_log::Print( u8"ECS::Initialize", ecs_log_level::Info );
#endif // DEBUG

        ecs_Components::Initialize();
        ecs_Events::Initialize();
        ecs_Entities::Initialize();
        ecs_Systems::Initialize();
    }

    void ECSEngine::Terminate()
    {
#if defined( ECS_DEBUG ) // DEBUG
        ecs_log::Print( u8"ECS::Terminate", ecs_log_level::Info );
#endif // DEBUG

        ecs_Components::Terminate();
        ecs_Events::Terminate();
        ecs_Entities::Terminate();
        ecs_Systems::Terminate();
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
