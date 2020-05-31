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

#ifndef ECS_COMPONENT_HPP
#define ECS_COMPONENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::api
#ifndef ECS_API_HPP
#include "../types/ecs_api.hpp"
#endif // !ECS_API_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "../types/ecs_mutex.hpp"
#endif // ECS_MUTEX_HPP

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * Component - base component struct.
     *
     * @version 0.1
    **/
    struct ECS_API Component
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_STRUCT

        // ===========================================================
        // CONSTANTS
        // ===========================================================

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** Component-ID **/
        const ecs_ObjectID mID;

        /** Type-ID. Used instead of a template value to avoid templates & virtual-calls combination. **/
        const ecs_TypeID mTypeID;

        /** Mutex. **/
        ecs_Mutex* const mMutex;

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * Component constructor.
         *
         * @param pType - Type-ID
         * @param pMutex - Mutex, null if not used. Value deleted in destructor.
         * @throws - can throw exception.
        **/
        explicit Component( const ecs_TypeID pType, ecs_Mutex* const pMutex = nullptr );

        /**
         * @brief
         * Component destructor.
         *
         * @throws - no exceptions.
        **/
        virtual ~Component() ECS_NOEXCEPT;

        // -----------------------------------------------------------

    }; /// ecs::Component

    // -----------------------------------------------------------

} /// ecs

using ecs_Component = ecs::Component;
#define ECS_COMPONENT_DECL

// -----------------------------------------------------------

#endif // !ECS_COMPONENT_HPP
