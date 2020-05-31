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

#ifndef ECS_COMPONENTS_MANAGER_HPP
#define ECS_COMPONENTS_MANAGER_HPP

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

// Forward-Declare ecs::Component
#ifndef ECS_COMPONENT_DECL
#define ECS_COMPONENT_DECL
namespace ecs { struct Component; }
using ecs_Component = ecs::Component;
#endif // !ECS_COMPONENT_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * ComponentsManager - handles Components managment.
     *
     * @version 0.1
    **/
    class ECS_API ComponentsManager final : public ecs_IMapIterator
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

        /** Component pointer. **/
        using ecs_comp_ptr = ecs_sptr<ecs_Component>;

        /** Components map by Object-ID. **/
        using ecs_comps_objects_map = ecs_async_map<ecs_ObjectID, ecs_comp_ptr>;

        /** Components map by Object-ID pointer. **/
        using ecs_comp_objects_map_ptr = ecs_sptr<ecs_comps_objects_map>;

        /** Components map by Type-ID. **/
        using ecs_comps_types_map = ecs_async_map<ecs_TypeID, ecs_comp_objects_map_ptr>;

        // -----------------------------------------------------------

    private:

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** ComponentsManager instance. **/
        static ecs_sptr<ComponentsManager> mInstance;

        /** Components map. **/
        ecs_comps_types_map mTypedComponents;

        /** IDStorage **/
        ecs_IDMap<ecs_TypeID, ecs_ObjectID> mIDStorage;

        // ===========================================================
        // DELETED
        // ===========================================================

        ComponentsManager(const ComponentsManager&) = delete;
        ComponentsManager& operator=(const ComponentsManager&) = delete;
        ComponentsManager(ComponentsManager&&) = delete;
        ComponentsManager& operator=(ComponentsManager&&) = delete;

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns weak-pointer to ComponentsManager isntance.
         *
         * (?) To support thread-safe isntance sharing without locking.
         * shared-pointer stored, and all accesses gained through weak-pointer.
         *
         * @thread_safety - thread-safe due to atomic nature.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_sptr<ComponentsManager> getInstance();

        /**
         * @brief
         * Returns Components container or null.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param componentsManager - ComponentsManager isntance.
         * @param pAllocate - 'true' to add, if not found.
         * @throws - can throw exception.
        **/
        static ECS_API ecs_comp_objects_map_ptr getComponents( const ecs_TypeID pType, ecs_sptr<ComponentsManager>& componentsManager, const bool pAllocate = false);

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * ComponentsManager constructor.
         *
         * @throws - cant throw exception.
        **/
        explicit ComponentsManager();

        /**
         * @brief
         * ComponentsManager destructor.
         *
         * @throws - can throw exception.
        **/
        ~ComponentsManager();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns Component or null.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - Component ID.
         * @param pRemove - 'true' to remove Component from the storage.
         * @throws - no exceptions.
        **/
        static ECS_API ecs_comp_ptr getComponent( const ecs_TypeID pType, const ecs_ObjectID pID, const bool pRemove = false ) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns any available Component of the given type.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Component Type.
         * @param pRemove - 'true' to remove Component from the storage.
         * @throws - no exceptions.
        **/
        static ECS_API ecs_comp_ptr getAnyComponent(const ecs_TypeID pType, const bool pRemove = false) ECS_NOEXCEPT;

        // ===========================================================
        // bt::core::IMapIterator
        // ===========================================================

        /**
         * @brief
         * Called on map iteration.
         *
         * @thread_safety - called while thread-lock.
         * @param pKey - Key.
         * @param pVal - Value.
         * @return 'true' to stop & return value.
         * @throws - no exceptions.
        **/
        virtual const void* onIterateMap(const void* pKey, void* pVal) BT_NOEXCEPT final;

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Adds Component to the storage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pComponent - Component to store.
         * @throws - can throw exception.
        **/
        static ECS_API void addComponent( const ecs_TypeID pType, ecs_comp_ptr pComponent );

        /**
         * @brief
         * Removes Component from the storage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - Component ID.
         * @throws - no exceptions.
        **/
        static ECS_API void removeComponentByID( const ecs_TypeID pType, const ecs_ObjectID pID ) ECS_NOEXCEPT;

        /**
         * @brief
         * Removes Component from the storage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - Component ID.
         * @throws - no exceptions.
        **/
        static ECS_API void removeComponent(const ecs_TypeID pType, ecs_comp_ptr& pComponent) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns Component ID.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        static ecs_ObjectID generateComponentID(const ecs_TypeID pType) ECS_NOEXCEPT;

        /**
         * @brief
         * Returns Component ID for reusage.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID to return for reusage.
         * @throws - can throw exception.
        **/
        static void releaseComponentID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT;

        /**
         * @brief
         * Initialize ComponentsManager instance.
         * 
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Initialize();

        /**
         * @brief
         * Terminate ComponentsManager instance.
         *
         * @thread_safety - main thread only.
         * @throws - can throw exception.
        **/
        static ECS_API void Terminate();
        
        // -----------------------------------------------------------

    }; /// ecs::ComponentsManager

    // -----------------------------------------------------------

} /// ecs

using ecs_ComponentsManager = ecs::ComponentsManager;
#define ECS_COMPONENTS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !ECS_COMPONENTS_MANAGER_HPP
