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
#ifndef ECS_ENTITIES_MANAGER_HPP
#include "../../../public/bt/ecs/entity/EntitiesManager.hpp"
#endif // !ECS_ENTITIES_MANAGER_HPP

// Include ecs::IEntity
#ifndef ECS_I_ENTITY_HXX
#include "../../../public/bt/ecs/entity/IEntity.hxx"
#endif // !ECS_I_ENTITY_HXX

// ===========================================================
// ecs::EntitiesManager
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    ecs_AsyncStorage<ecs_sptr<EntitiesManager>> EntitiesManager::mInstanceHolder;

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    EntitiesManager::EntitiesManager()
        : mIDStorage(),
          mIDMutex(),
          mEntities(),
          mEntitiesMutex()
    {
    }

    EntitiesManager::~EntitiesManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_sptr<EntitiesManager> EntitiesManager::getInstance()
    { return mInstanceHolder.getItem(); }

    EntitiesManager::ecs_entities_map_storage& EntitiesManager::getEntities( const ecs_TypeID pType )
    {
        ecs_SpinLock lock( &mEntitiesMutex );
        return mEntities[pType];
    }

    EntitiesManager::entity_ptr EntitiesManager::getEntityByType( const ecs_TypeID pType, const bool pRemove )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return entity_ptr( nullptr );

        ecs_entities_map_storage& entitiesStorage = instance->getEntities( pType );
        ecs_SpinLock lock( &entitiesStorage.mMutex );

        auto pos = entitiesStorage.mItem.begin();
        auto end = entitiesStorage.mItem.cend();

        entity_ptr result;
        while( pos != end )
        {
            result = pos->second;

            if ( result != nullptr )
                return result;

            pos++;
        }

        return entity_ptr( nullptr );
    }

    EntitiesManager::entity_ptr EntitiesManager::getEntityByID( const ecs_TypeID pType, const ecs_ObjectID pID, const bool pRemove )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return entity_ptr( nullptr );

        ecs_entities_map_storage& entitiesStorage = instance->getEntities( pType );
        ecs_SpinLock lock( &entitiesStorage.mMutex );

        entity_ptr result = entitiesStorage.mItem[pID];

        if ( pRemove )
            entitiesStorage.mItem.erase( pID );

        return entitiesStorage.mItem[pID];
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    void EntitiesManager::registerEntity( entity_ptr& pEntity )
    {
        auto instance = getInstance();

        if ( instance == nullptr || pEntity == nullptr )
            return;

        ecs_entities_map_storage& entitiesStorage = instance->getEntities( pEntity->getTypeID() );
        ecs_SpinLock lock( &entitiesStorage.mMutex );

        entitiesStorage.mItem[pEntity->getID()] = pEntity;
    }

    void EntitiesManager::unregisterEntity( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        auto instance = getInstance();

        if ( instance == nullptr )
            return;

        ecs_entities_map_storage& entitiesStorage = instance->getEntities( pType );
        ecs_SpinLock lock( &entitiesStorage.mMutex );

        entitiesStorage.mItem.erase( pID );
    }

    ecs_ObjectID EntitiesManager::generateEntityID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<ecs_Entities> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mIDMutex );
            return instance->mIDStorage.getAvailableID(pType);
        }

        return ECS_INVALID_OBJECT_ID;
    }

    void EntitiesManager::releaseEntityID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<ecs_Entities> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mIDMutex );
            instance->mIDStorage.releaseID(pType, pID);
        }
    }

    void EntitiesManager::Initialize()
    {
        if ( getInstance() == nullptr )
            mInstanceHolder.setItem( ecs_Shared<ecs_Entities>() );
    }

    void EntitiesManager::Terminate()
    { mInstanceHolder.setItem( bt_sptr<ecs_Entities>( nullptr ) ); }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------