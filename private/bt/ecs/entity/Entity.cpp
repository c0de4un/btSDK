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
#ifndef ECS_ENTITY_HPP
#include "../../../../public/bt/ecs/entity/Entity.hpp"
#endif // !ECS_ENTITY_HPP

// Include ecs::EntitiesManager
#ifndef ECS_ENTITIES_MANAGER_HPP
#include "../../../../public/bt/ecs/entity/EntitiesManager.hpp"
#endif // !ECS_ENTITIES_MANAGER_HPP

// Include ecs::Component
#ifndef ECS_COMPONENT_HPP
#include "../../../../public/bt/ecs/component/Component.hpp"
#endif // !ECS_COMPONENT_HPP

// ===========================================================
// ecs::Entity
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    Entity::Entity( const ecs_TypeID pType )
        : mComponentsMutex(),
          mComponents(),
          mChildren(),
          mChildrenMutex(),
          mParent(),
          mTypeID( pType ),
          mID( ecs_Entities::generateEntityID( mTypeID ) )
    {
    }

    Entity::~Entity()
    {
        ecs_Entities::releaseEntityID( mTypeID, mID );
    }

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ecs_TypeID Entity::getTypeID() const noexcept
    { return mTypeID; }

    ecs_TypeID Entity::getID() const noexcept
    { return mID; }

    ecs_sptr<ecs_Component> Entity::getComponent( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        ecs_SpinLock lock(&mComponentsMutex );
        ecs_map<ecs_ObjectID, ecs_sptr<ecs_Component>>& components = mComponents[pType];
        return components[pID];
    }

    ecs_sptr<IEntity> Entity::getChild( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        ecs_SpinLock lock( &mChildrenMutex );

        for( ecs_sptr<IEntity>& child : mChildren )
        {
            if ( child->getTypeID() == pType && child->getID() == pID )
                return child;
        }

        return ecs_sptr<IEntity>( nullptr );
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    bool Entity::onAttachToEntity( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        ecs_sptr<IEntity> parent = ecs_Entities::getEntityByID( pType, pID, false );

        if ( parent != nullptr )
            mParent = ecs_Memory::MakeWeak<ecs_IEntity>( parent );

        return true;
    }

    void Entity::onDetachFromEntity( const ecs_TypeID pType, const ecs_ObjectID pID )
    { mParent.reset(); }

    // ===========================================================
    // IEntity
    // ===========================================================

    void Entity::attachComponent( ecs_sptr<ecs_Component> pComponent )
    {
        ecs_SpinLock lock( &mComponentsMutex );
        ecs_map<ecs_ObjectID, ecs_sptr<ecs_Component>>& components = mComponents[pComponent->mTypeID];
        components[pComponent->mID] = pComponent;
    }

    void Entity::detachComponent( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        ecs_SpinLock lock( &mComponentsMutex );
        ecs_map<ecs_ObjectID, ecs_sptr<ecs_Component>>& components = mComponents[pType];
        components.erase( pID );
    }

    bool Entity::attachEntity( ecs_sptr<IEntity> pEntity )
    {
        ecs_SpinLock lock( &mChildrenMutex );
        ecs_sptr<Entity> child = ecs_Memory::StaticCast<Entity, IEntity>( pEntity );
        if ( child->onAttachToEntity(mTypeID, mID) )
        {
            mChildren.push_back(pEntity);
            return true;
        }

        return false;
    }

    void Entity::detachEntity( const ecs_TypeID pType, const ecs_ObjectID pID )
    {
        ecs_sptr<IEntity> child = getChild( pType, pID );

        if ( child != nullptr )
        {
            ecs_SpinLock lock( &mChildrenMutex );
            ecs_VectorUtil<ecs_sptr<IEntity>>::SwapPop( mChildren, child );
        }
    }

    void Entity::Destroy()
    { ecs_Entities::unregisterEntity( getTypeID(), mID ); }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
