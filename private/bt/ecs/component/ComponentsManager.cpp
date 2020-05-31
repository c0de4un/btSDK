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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef ECS_COMPONENTS_MANAGER_HPP
#include "../../../../public/bt/ecs/component/ComponentsManager.hpp"
#endif // !ECS_COMPONENTS_MANAGER_HPP

// Include ecs::Component
#ifndef ECS_COMPONENT_HPP
#include "../../../../public/bt/ecs/component/Component.hpp"
#endif // !ECS_COMPONENT_HPP

// ===========================================================
// ecs::ComponentsManager
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    ecs_sptr<ComponentsManager> ComponentsManager::mInstance(nullptr);

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    ComponentsManager::ComponentsManager()
        : mTypedComponents(),
        mIDStorage()
    {
    }

    ComponentsManager::~ComponentsManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_sptr<ComponentsManager> ComponentsManager::getInstance()
    {
        return mInstance; // Copy-Construct
    }

    ComponentsManager::ecs_comp_objects_map_ptr ComponentsManager::getComponents(const ecs_TypeID pType, ecs_sptr<ComponentsManager>& componentsManager, const bool pAllocate)
    {
        ecs_comp_objects_map_ptr result = nullptr;
        if ( componentsManager != nullptr )
        {
            ecs_comps_types_map& typesMap = componentsManager->mTypedComponents;

            if ( typesMap.Contains(pType) )
                result = typesMap[pType];
            else if ( pAllocate )
            {
                typesMap.Insert( pType, ecs_comp_objects_map_ptr( ecs_Memory::MakeShared<ecs_comps_objects_map>() ) );
                result = typesMap[pType];
            }
        }

        return result;
    }

    ComponentsManager::ecs_comp_ptr ComponentsManager::getComponent(const ecs_TypeID pType, const ecs_ObjectID pID, const bool pRemove) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        ecs_comp_objects_map_ptr objectsMap = getComponents(pType, componentsManager);

        if ( !pRemove )
            return ( objectsMap && objectsMap->Contains(pID) ? objectsMap->Get(pID) : ecs_comp_ptr() );

        ecs_comp_ptr result = nullptr;
        if ( objectsMap != nullptr && objectsMap->Contains(pID) )
        {
            ecs_comp_ptr result = objectsMap->Get(pID);
            objectsMap->Erase(pID);
        }

        return result;
    }

    ComponentsManager::ecs_comp_ptr ComponentsManager::getAnyComponent(const ecs_TypeID pType, const bool pRemove) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        ecs_comp_objects_map_ptr objectsMap = getComponents(pType, componentsManager);
        ecs_comp_ptr result;

        if ( objectsMap != nullptr )
        {
            ComponentsManager* const componentsManager_raw = ecs_Memory::GetRawPointer<ComponentsManager>(componentsManager);
            const ecs_ObjectID* componentId = 0;
            while ( !objectsMap->isEmpty() && !componentId )
            {
                if ( (componentId = static_cast<const ecs_ObjectID*>( objectsMap->Iterate(componentsManager_raw) )) != nullptr )
                {
                    result = objectsMap->Get(*componentId);
                    break;
                }
            }

            if ( pRemove )
                objectsMap->Erase(result->mID);
        }

        return result;
    }

    // ===========================================================
    // bt::core::IMapIterator
    // ===========================================================

    const void* ComponentsManager::onIterateMap(const void* pKey, void* pVal) BT_NOEXCEPT
    {
        ecs_comp_ptr* value_raw = pVal ? static_cast<ecs_comp_ptr*>(pVal) : nullptr;
        return ( value_raw && *(value_raw) != nullptr ) ? pKey : nullptr;
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    void ComponentsManager::addComponent(const ecs_TypeID pType, ecs_comp_ptr pComponent)
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        ecs_comp_objects_map_ptr objectsMap = getComponents(pType, componentsManager, true);

        objectsMap->Insert( pComponent->mID, pComponent, true );
    }

    void ComponentsManager::removeComponentByID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        ecs_comp_objects_map_ptr objectsMap = getComponents(pType, componentsManager);

        if ( objectsMap != nullptr )
            objectsMap->Erase( pID );
    }

    void ComponentsManager::removeComponent(const ecs_TypeID pType, ecs_comp_ptr& pComponent) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        ecs_comp_objects_map_ptr objectsMap = getComponents(pType, componentsManager);

        if ( objectsMap != nullptr )
            objectsMap->Erase(pComponent->mID);
    }

    ecs_ObjectID ComponentsManager::generateComponentID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();
        return componentsManager != nullptr ? componentsManager->mIDStorage.getAvailableID(pType) : ECS_INVALID_OBJECT_ID;
    }

    void ComponentsManager::releaseComponentID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();

        if ( componentsManager != nullptr )
            componentsManager->mIDStorage.releaseID(pType, pID);
    }

    void ComponentsManager::Initialize()
    {
        if ( mInstance != nullptr )
            return;

        mInstance = ecs_new<ComponentsManager>();
    }

    void ComponentsManager::Terminate()
    {
        if ( mInstance == nullptr )
            return;

        mInstance = nullptr;
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
