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

#ifndef ECS_I_SYSTEM_HXX
#define ECS_I_SYSTEM_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::api
#ifndef ECS_API_HPP
#include "../types/ecs_api.hpp"
#endif // !ECS_API_HPP

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
     * ISystem - System interface.
     *
     * @version 0.1
    **/
    class ECS_API ISystem
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_INTERFACE

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * ISystem destructor.
         *
         * @throws - can throw exceptions.
        **/
        virtual ~ISystem()
        {
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns Type-ID.
         *
         * @thread_safety - not required.
         * @throws - no exceptions.
        **/
        virtual ecs_TypeID getTypeID() const BT_NOEXCEPT = 0;

        /**
         * @brief
         * Returns System ID.
         *
         * @throws - no exceptions.
        **/
        virtual ecs_ObjectID getID() const BT_NOEXCEPT = 0;

        /**
         * @brief
         * Returns 'true' if paused.
         *
         * @thread_safety - atomic used.
         * @throws - no exceptions.
        **/
        virtual bool isPaused() const noexcept = 0;

        /**
         * @brief
         * Returns 'true' if System started.
         *
         * @thread_safety - atomic used.
         * @throws - no exceptions.
        **/
        virtual bool isStarted() const noexcept = 0;

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Start/Resume System.
         *
         * @thread_safety - thread-locks used.
         * @return - 'true' if OK, 'false' if error.
         * @throws - can throw exception.
        **/
        virtual bool Start() = 0;

        /**
         * @brief
         * Pause System.
         *
         * @thread_safety - thread-locks used.
         * @throws - can throw exception.
        **/
        virtual void Pause() = 0;

        /**
         * @brief
         * Stop System.
         * Unlikely #Pause, release (unload) all related resources.
         *
         * @thread_safety - thread-locks used.
         * @throws - no exceptions.
        **/
        virtual void Stop() = 0;

        // -----------------------------------------------------------

    }; /// ecs::ISystem

    // -----------------------------------------------------------

} /// ecs

using ecs_ISystem = ecs::ISystem;
#define ECS_I_SYSTEM_DECL

// -----------------------------------------------------------

#endif // !ECS_I_SYSTEM_HXX
