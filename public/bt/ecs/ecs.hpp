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

#ifndef BT_ECS_HPP
#define BT_ECS_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::memory
#ifndef ECS_API_HPP
#include "types/ecs_api.hpp"
#endif // !ECS_API_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "types/ecs_mutex.hpp"
#endif // !ECS_MUTEX_HPP

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * ECSEngine - ECS wrapper.
     *
     * @version 0.1
    **/
    class ECS_API ECSEngine
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_CLASS

        // -----------------------------------------------------------

    private:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR
        // ===========================================================

        /**
         * @brief
         * ECSEngine constructor.
         *
         * @throws - can throw exception.
        **/
        explicit ECSEngine();

        // ===========================================================
        // DELETED
        // ===========================================================

        ECSEngine(const ECSEngine&) = delete;
        ECSEngine& operator=(const ECSEngine&) = delete;
        ECSEngine(ECSEngine&&) = delete;
        ECSEngine& operator=(ECSEngine&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * ECSEngine destructor.
         *
         * @throws - no exceptions.
        **/
        ~ECSEngine() ECS_NOEXCEPT;

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Initialize ECS.
         *
         * @thread_safety - main thread-only.
         * @throws - can throw exception.
        **/
        static void Initialize();

        /**
         * @brief
         * Terminate ECS.
         *
         * @thread_safety - main thread-only.
         * @throws - can throw exception.
        **/
        static void Terminate();

        // -----------------------------------------------------------

    }; /// bt::ECSEngine

    // -----------------------------------------------------------

} /// ecs

using ecs_Engine = ecs::ECSEngine;

// -----------------------------------------------------------

#endif // !BT_ECS_HPP
