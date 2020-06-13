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

#ifndef ECS_SYSTEMS_MANAGER_HPP
#define ECS_SYSTEMS_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::ids
#ifndef ECS_IDS_HPP
#include "../types/ecs_ids.hpp"
#endif // !ECS_IDS_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "../types/ecs_mutex.hpp"
#endif // ECS_MUTEX_HPP

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// Include ecs::map
#ifndef ECS_MAP_HPP
#include "../types/ecs_map.hpp"
#endif // !ECS_MAP_HPP

// ===========================================================
// FORWARD-DECLARATION
// ===========================================================

// Forward-Declare ecs::ISystem
#ifndef ECS_I_SYSTEM_DECL
#define ECS_I_SYSTEM_DECL
namespace ecs { class ISystem; }
using ecs_ISystem = ecs::ISystem;
#endif // !ECS_I_SYSTEM_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * SystemsManager - stores & manage Systems.
     *
     * @version 0.1
    **/
    class ECS_API SystemsManager
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
        // TYPES
        // ===========================================================

        /** System pointer. **/
        using system_ptr = ecs_sptr<ecs_ISystem>;

        /** Systems map. **/
        using systems_map = ecs_map<ecs_TypeID, system_ptr>;

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** ComponentsManager instance. **/
        static ecs_sptr<SystemsManager> mInstance;

        /** IDStorage **/
        ecs_IDMap<ecs_TypeID, ecs_ObjectID> mIDStorage;

        /** Systems. **/
        systems_map mSystems;

        /** Systems Mutex. **/
        ecs_Mutex mSystemsMutex;

        /** Mutex. **/
        ecs_Mutex mIDMutex;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns weak-pointer to ComponentsManager isntance.
         *
         * @thread_safety - thread-safe due to atomic nature.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_sptr<SystemsManager> getInstance();

        // ===========================================================
        // DELETED
        // ===========================================================

        SystemsManager(const SystemsManager&) = delete;
        SystemsManager& operator=(const SystemsManager&) = delete;
        SystemsManager(SystemsManager&&) = delete;
        SystemsManager& operator=(SystemsManager&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * SystemsManager constructor.
         *
         * @throws - can throw exception.
        **/
        explicit SystemsManager();

        /**
         * @brief
         * SystemsManager destructor.
         *
         * @throws - can throw exception.
        **/
        ~SystemsManager();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Returns System ID.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_ObjectID generateSystemID(const ecs_TypeID pType) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns System ID for reusage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID to return for reusage.
         * @throws - can throw exception.
        **/
        static ECS_API void releaseSystemID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT;

        /**
         * @brief
         * Store System instance.
         *
         * @thread_safety - thread-locks used.
         * @param pSystem - System instance.
         * @throws - can throw exception.
        **/
        static ECS_API void registerSystem( system_ptr& pSystem );

        /**
         * @brief
         * Remove System.
         *
         * @thread_safety - thread-locks used.
         * @param pType - System Type-ID.
         * @throws - can throw exception.
        **/
        static ECS_API void unregisterSystem( const ecs_TypeID pType );

        /**
         * @brief
         * Initialize SystemsManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Initialize();

        /**
         * @brief
         * Terminate SystemsManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Terminate();

        // -----------------------------------------------------------

    }; /// ecs::SystemsManager

    // -----------------------------------------------------------

} /// ecs

using ecs_Systems = ecs::SystemsManager;
#define ECS_SYSTEMS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !ECS_SYSTEMS_MANAGER_HPP
