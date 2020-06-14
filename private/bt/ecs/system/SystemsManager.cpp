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
#ifndef ECS_SYSTEMS_MANAGER_HPP
#include "../../../../public/bt/ecs/system/SystemsManager.hpp"
#endif // !ECS_SYSTEMS_MANAGER_HPP

// Include ecs::ISystem
#ifndef ECS_I_SYSTEM_HXX
#include "../../../../public/bt/ecs/system/ISystem.hxx"
#endif // !ECS_I_SYSTEM_HXX

// ===========================================================
// ecs::SystemsManager
// ===========================================================

namespace ecs
{

    // -----------------------------------------------------------

    // ===========================================================
    // FIELDS
    // ===========================================================

    ecs_sptr<SystemsManager> SystemsManager::mInstance(nullptr);

    // ===========================================================
    // CONSTRUCTOR & DESTRUCTOR
    // ===========================================================

    SystemsManager::SystemsManager()
        : mIDStorage(),
        mSystems(),
        mSystemsMutex(),
        mIDMutex()
    {
    }

    SystemsManager::~SystemsManager() = default;

    // ===========================================================
    // GETTERS & SETTERS
    // ===========================================================

    ECS_API ecs_sptr<SystemsManager> SystemsManager::getInstance()
    { return mInstance; }

    ECS_API SystemsManager::system_ptr SystemsManager::getSystem( const ecs_TypeID pType )
    {
        auto instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock(&instance->mSystemsMutex);
            return instance->mSystems[pType];
        }

        return system_ptr( nullptr );
    }

    // ===========================================================
    // METHODS
    // ===========================================================

    ECS_API ecs_ObjectID SystemsManager::generateSystemID(const ecs_TypeID pType) ECS_NOEXCEPT
    {
        ecs_sptr<SystemsManager> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock(&instance->mIDMutex);

            return instance->mIDStorage.getAvailableID(pType);
        }

        return ECS_INVALID_OBJECT_ID;
    }

    ECS_API void SystemsManager::releaseSystemID(const ecs_TypeID pType, const ecs_ObjectID pID) ECS_NOEXCEPT
    {
        ecs_sptr<SystemsManager> instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mIDMutex );
            instance->mIDStorage.releaseID(pType, pID);
        }
    }

    ECS_API void SystemsManager::registerSystem( system_ptr& pSystem )
    {
        auto instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock(&instance->mSystemsMutex);
            instance->mSystems[pSystem->getTypeID()] = pSystem;
        }
    }

    ECS_API void SystemsManager::unregisterSystem( const ecs_TypeID pType )
    {
        auto instance = getInstance();

        if ( instance != nullptr )
        {
            ecs_SpinLock lock( &instance->mSystemsMutex );
            instance->mSystems.erase( pType );
        }
    }

    ECS_API void SystemsManager::Initialize()
    {
        if ( mInstance == nullptr )
            mInstance = ecs_Shared<SystemsManager>();
    }

    ECS_API void SystemsManager::Terminate()
    {
        mInstance = nullptr;
    }

    // -----------------------------------------------------------

} /// ecs

// -----------------------------------------------------------
