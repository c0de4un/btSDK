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

#ifndef ECS_ENTITIES_MANAGER_HPP
#define ECS_ENTITIES_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::api
#ifndef ECS_API_HPP
#include "../types/ecs_api.hpp"
#endif // !ECS_API_HPP

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

// Forward-Declare ecs::IEntity
#ifndef ECS_I_ENTITY_DECL
#define ECS_I_ENTITY_DECL
namespace ecs { class IEntity; }
using ecs_IEntity = ecs::IEntity;
#endif // !ECS_I_ENTITY_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * EntitiesManager - manages Entities & their IDs.
     *
     * @version 0.1
    **/
    class ECS_API EntitiesManager final
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        ECS_CLASS

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONFIGS
        // ===========================================================

        /** Entity Pointer. **/
        using entity_ptr = ecs_sptr<ecs_IEntity>;

        /** Entities map. **/
        using etities_map = ecs_map<ecs_ObjectID, entity_ptr>;

        /** Entities map container. **/
        using ecs_entities_map_storage = ecs_AsyncStorage<etities_map>;

        /** Entities types-map. **/
        using entities_types_map = ecs_map<ecs_TypeID, ecs_entities_map_storage>;

        // -----------------------------------------------------------

    private:

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** ComponentsManager instance. **/
        static ecs_AsyncStorage<ecs_sptr<EntitiesManager>> mInstanceHolder;

        /** IDStorage **/
        ecs_IDMap<ecs_TypeID, ecs_ObjectID> mIDStorage;

        /** IDStorage Mutex. **/
        ecs_Mutex mIDMutex;

        /** Entities **/
        entities_types_map mEntities;

        /** Entities Mutex. **/
        ecs_Mutex mEntitiesMutex;

        // ===========================================================
        // DELETED
        // ===========================================================

        EntitiesManager(const EntitiesManager&) = delete;
        EntitiesManager& operator=(const EntitiesManager&) = delete;
        EntitiesManager(EntitiesManager&&) = delete;
        EntitiesManager& operator=(EntitiesManager&&) = delete;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns weak-pointer to EntitiesManager isntance.
         *
         * @thread_safety - thread-safe due to atomic nature.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_sptr<EntitiesManager> getInstance();

        /**
         * @brief
         * Returns Entities collection by Type-ID.
         *
         * @thread_safety - thread-lock used.
         * @throws - can throw exception.
        **/
        ecs_entities_map_storage& getEntities( const ecs_TypeID pType );

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * EntitiesManager constructor.
         *
         * @throws - cant throw exception.
        **/
        explicit EntitiesManager();

        /**
         * @brief
         * EntitiesManager destructor.
         *
         * @throws - can throw exception.
        **/
        ~EntitiesManager();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Search Entity by Type-ID.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pRemove - 'true' to remove Entity from the storage.
         * @throws - can throw exception.
        **/
        static entity_ptr getEntityByType( const ecs_TypeID pType, const bool pRemove );

        /**
         * @brief
         * Search Entity.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @param pRemove - 'true' to remove Entity from the storage.
         * @throws - can throw exception.
        **/
        static entity_ptr getEntityByID( const ecs_TypeID pType, const ecs_ObjectID pID, const bool pRemove );

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Add Entity (store).
         *
         * @thread_safety - thread-locks used.
         * @param pEntity - Entity instance to store.
         * @throws - can throw exception.
        **/
        static ECS_API void registerEntity( entity_ptr& pEntity );

        /**
         * @brief
         * Remove Entity.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        static ECS_API void unregisterEntity( const ecs_TypeID pType, const ecs_ObjectID pID );

        /**
         * @brief
         * Returns Entity ID.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_ObjectID generateEntityID(const ecs_TypeID pType) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns EntitiesManager ID for reuse.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID to return for reuse.
         * @throws - can throw exception.
        **/
        static ECS_API void releaseEntityID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT;

        /**
         * @brief
         * Initialize EntitiesManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Initialize();

        /**
         * @brief
         * Terminate EntitiesManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Terminate();

        // -----------------------------------------------------------

    }; /// ecs::EntitiesManager

    // -----------------------------------------------------------

} /// ecs

using ecs_Entities = ecs::EntitiesManager;

// -----------------------------------------------------------

#endif // !ECS_ENTITIES_MANAGER_HPP
