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
          mComponentsMutex(),
          mIDStorage(),
          mIDMutex()
    {
    }

    ComponentsManager::~ComponentsManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_sptr<ComponentsManager> ComponentsManager::getInstance()
    { return mInstance; }

    ComponentsManager::components_map_storage& ComponentsManager::getComponents(const ecs_TypeID pType)
    {
        ecs_SpinLock lock( &mComponentsMutex );
        return mTypedComponents[pType];
    }

    ComponentsManager::ecs_comp_ptr ComponentsManager::getComponent(const ecs_TypeID pType, const ecs_ObjectID pID, const bool pRemove) ECS_NOEXCEPT
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return ecs_comp_ptr( nullptr );

        components_map_storage& componentsStorage = instance->getComponents( pType );
        ecs_SpinLock lock( &componentsStorage.mMutex );

        ecs_comp_ptr result = componentsStorage.mItem[pID];

        if ( result != nullptr && pRemove )
            componentsStorage.mItem.erase(pID);

        return result;
    }

    ComponentsManager::ecs_comp_ptr ComponentsManager::getAnyComponent(const ecs_TypeID pType, const bool pRemove) ECS_NOEXCEPT
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return ecs_comp_ptr( nullptr );

        components_map_storage& componentsStorage = instance->getComponents( pType );
        ecs_SpinLock lock( &componentsStorage.mMutex );

        auto pos = componentsStorage.mItem.begin();
        auto end = componentsStorage.mItem.cend();

        ecs_comp_ptr result = nullptr;
        while( pos != end )
        {
            result = pos->second;

            if ( result != nullptr )
            {
                if ( pRemove )
                    componentsStorage.mItem.erase(result->mID);

                break;
            }

            pos++;
        }

        return result;
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    void ComponentsManager::addComponent(ecs_comp_ptr& pComponent)
    {
        auto instance = getInstance();

        if ( instance == nullptr || pComponent == nullptr )
            return;

        components_map_storage& componentsStorage = instance->getComponents( pComponent->mTypeID );
        ecs_SpinLock lock( &componentsStorage.mMutex );
        componentsStorage.mItem[pComponent->mID] = pComponent;
    }

    void ComponentsManager::removeComponentByID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        components_map_storage& componentsStorage = instance->getComponents( pType );
        ecs_SpinLock lock( &componentsStorage.mMutex );
        componentsStorage.mItem.erase( pID );
    }

    void ComponentsManager::removeComponent(ecs_comp_ptr& pComponent) ECS_NOEXCEPT
    {
        auto instance = getInstance();

        if ( instance == nullptr || pComponent == nullptr )
            return;

        components_map_storage& componentsStorage = instance->getComponents( pComponent->mTypeID );
        ecs_SpinLock lock( &componentsStorage.mMutex );
        componentsStorage.mItem.erase( pComponent->mID );
    }

    ecs_ObjectID ComponentsManager::generateComponentID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();

        if ( componentsManager != nullptr )
        {
            ecs_SpinLock lock( &componentsManager->mIDMutex );
            return componentsManager->mIDStorage.getAvailableID(pType);
        }

        return ECS_INVALID_OBJECT_ID;
    }

    void ComponentsManager::releaseComponentID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<ComponentsManager> componentsManager = getInstance();

        if ( componentsManager != nullptr )
        {
            ecs_SpinLock lock( &componentsManager->mIDMutex );
            componentsManager->mIDStorage.releaseID(pType, pID);
        }
    }

    void ComponentsManager::Initialize()
    {
        if ( mInstance == nullptr )
            mInstance = ecs_Shared<ComponentsManager>();
    }

    void ComponentsManager::Terminate()
    { mInstance = nullptr; }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
