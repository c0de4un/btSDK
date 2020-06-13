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

#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::IEntity
#ifndef ECS_I_ENTITY_HXX
#include "IEntity.hxx"
#endif // !ECS_I_ENTITY_HXX

// Include ecs::AsyncMap
#ifndef ECS_MAP_HPP
#include "../types/ecs_map.hpp"
#endif // !ECS_MAP_HPP

// Include ecs::AsyncVector
#ifndef ECS_VECTOR_HPP
#include "../types/ecs_vector.hpp"
#endif // !ECS_VECTOR_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    /**
     * @brief
     * Entity - base Entity class.
     *
     * @version 0.1
    **/
    class ECS_API Entity : public ecs_IEntity
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        BT_CLASS

        // -----------------------------------------------------------

    protected:

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        /** Components Mutex. **/
        ecs_Mutex mComponentsMutex;

        /** Attached Components. **/
        ecs_map<ecs_TypeID, ecs_map<ecs_ObjectID, ecs_sptr<ecs_Component>>> mComponents;

        /** Attached IEntity. **/
        ecs_vec<ecs_sptr<ecs_IEntity>> mChildren;

        /** Attached IEntities Mutex. **/
        ecs_Mutex mChildrenMutex;

        /** Parent IEntity. **/
        ecs_wptr<ecs_IEntity> mParent;

        // ===========================================================
        // CONSTRUCTOR
        // ===========================================================

        /**
         * @brief
         * Entity constructor.
         *
         * @param pType - Type-ID.
         * @throws - can throw exception.
        **/
        explicit Entity( const ecs_TypeID pType );

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Called to notify & ask Entity about attachment.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @return - 'true' to attach, 'false' to decline
         * @throws - can throw exception.
        **/
        virtual bool onAttachToEntity( const ecs_TypeID pType, const ecs_ObjectID pID );

        /**
         * @brief
         * Called to notify Entity about attachment.
         *
         * @thread_safety - thread-lock used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual void onDetachFromEntity( const ecs_TypeID pType, const ecs_ObjectID pID );

        // ===========================================================
        // DELETED
        // ===========================================================

        Entity(const Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) = delete;

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTANTS & FIELDS
        // ===========================================================

        /** Type-ID. **/
        const ecs_TypeID mTypeID;

        /** ID **/
        const ecs_ObjectID mID;

        // ===========================================================
        // DESTRUCTOR
        // ===========================================================

        /**
         * @brief
         * Entity destructor.
         *
         * @throws - can throw exception.
        **/
        virtual ~Entity();

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        /**
         * @brief
         * Returns Entity Type-ID.
         *
         * @thread_safety - not required.
         * @throws - no exceptions.
        **/
        virtual ecs_TypeID getTypeID() const noexcept final;

        /**
         * @brief
         * Returns Entity ID.
         *
         * @thread_safety - not required.
         * @throws - no exceptions.
        **/
        virtual ecs_TypeID getID() const noexcept final;

        /**
         * @brief
         * Returns Component, or null.
         *
         * @thread_safety -thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual ecs_sptr<ecs_Component> getComponent( const ecs_TypeID pType, const ecs_ObjectID pID ) final;

        /**
         * @brief
         * Search attached IEntity.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @return IEntity, or null.
         * @throws - can throw exception.
        **/
        virtual ecs_sptr<IEntity> getChild( const ecs_TypeID pType, const ecs_ObjectID pID ) final;

        // ===========================================================
        // IEntity
        // ===========================================================

        /**
         * @brief
         * Attach Component.
         *
         * @thread_safety - thread-locks used.
         * @param pComponent - Component to attach.
         * @throws - can throw exception.
        **/
        virtual void attachComponent( ecs_sptr<ecs_Component> pComponent ) override;

        /**
         * @brief
         * Detach Component.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual void detachComponent( const ecs_TypeID pType, const ecs_ObjectID pID ) override;

        /**
         * @brief
         * Attach Entity as Child.
         *
         * @thread_safety - thread-locks used.
         * @param pEntity - Child.
         * @reutrn 'true' if attached.
         * @throws - can throw exception.
        **/
        virtual bool attachEntity( ecs_sptr<IEntity> pEntity ) override;

        /**
         * @brief
         * Detach Entity.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual void detachEntity( const ecs_TypeID pType, const ecs_ObjectID pID ) override;

        /**
         * @brief
         * Queue this Entity for destruction.
         *
         * @thread_safety - thread-locks & atomics used.
         * @throws - can throw exception.
        **/
        virtual void Destroy() override;

        // -----------------------------------------------------------

    }; /// ecs::Entity

    // -----------------------------------------------------------

} /// ecs

#define ECS_ENTITY_DECL

// -----------------------------------------------------------

#endif // !ECS_ENTITY_HPP
