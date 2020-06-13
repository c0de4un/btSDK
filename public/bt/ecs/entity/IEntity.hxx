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

#ifndef ECS_I_ENTITY_HXX
#define ECS_I_ENTITY_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::numeric
#ifndef ECS_NUMERIC_HPP
#include "../types/ecs_numeric.hpp"
#endif // !ECS_NUMERIC_HPP

// Include ecs::memory
#ifndef ECS_MEMORY_HPP
#include "../types/ecs_memory.hpp"
#endif // !ECS_MEMORY_HPP

// Include ecs::mutex
#ifndef ECS_MUTEX_HPP
#include "../types/ecs_mutex.hpp"
#endif // !ECS_MUTEX_HPP

// ===========================================================
// FORWARD-DECLARATIONS
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
     * IEntity - Entity interface.
     *
     * @version 0.1
    **/
    class ECS_API IEntity
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
         * IEntity destructor.
         *
         * @throws - can throw exceptions.
        **/
        virtual ~IEntity()
        {
        }

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
        virtual ecs_TypeID getTypeID() const noexcept = 0;

        /**
         * @brief
         * Returns Entity ID.
         *
         * @thread_safety - not required.
         * @throws - no exceptions.
        **/
        virtual ecs_TypeID getID() const noexcept = 0;

        /**
         * @brief
         * Returns Component, or null.
         *
         * @thread_safety -thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual ecs_sptr<ecs_Component> getComponent( const ecs_TypeID pType, const ecs_ObjectID pID ) = 0;

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
        virtual ecs_sptr<IEntity> getChild( const ecs_TypeID pType, const ecs_ObjectID pID ) = 0;

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Attach Component.
         *
         * @thread_safety - thread-locks used.
         * @param pComponent - Component to attach.
         * @throws - can throw exception.
        **/
        virtual void attachComponent( ecs_sptr<ecs_Component> pComponent ) = 0;

        /**
         * @brief
         * Detach Component.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual void detachComponent( const ecs_TypeID pType, const ecs_ObjectID pID ) = 0;

        /**
         * @brief
         * Attach Entity as Child.
         *
         * @thread_safety - thread-locks used.
         * @param pEntity - Child.
         * @reutrn 'true' if attached.
         * @throws - can throw exception.
        **/
        virtual bool attachEntity( ecs_sptr<IEntity> pEntity ) = 0;

        /**
         * @brief
         * Detach Entity.
         *
         * @thread_safety - thread-locks used.
         * @param pType - Type-ID.
         * @param pID - ID.
         * @throws - can throw exception.
        **/
        virtual void detachEntity( const ecs_TypeID pType, const ecs_ObjectID pID ) = 0;

        /**
         * @brief
         * Queue this Entity for destruction.
         *
         * @thread_safety - thread-locks & atomics used.
         * @throws - can throw exception.
        **/
        virtual void Destroy() = 0;

        // -----------------------------------------------------------

    }; /// bt::IEntity

    // -----------------------------------------------------------

} /// ecs

using ecs_IEntity = ecs::IEntity;
#define ECS_I_ENTITY_DECL

// -----------------------------------------------------------

#endif // !ECS_I_ENTITY_HXX
