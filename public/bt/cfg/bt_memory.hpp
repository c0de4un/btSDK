/**
 * Copyright © 2020 Denis Z. (code4un@yandex.ru) All rights reserved.
 * Authors: Denis Z. (code4un@yandex.ru)
 * All rights reserved.
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
 */

#ifndef BT_CFG_MEMORY_HPP
#define BT_CFG_MEMORY_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "bt_api.hpp"
#endif // !BT_CFG_API_HPP

// PLATFORM
#if defined(ANDROID) || defined( BT_ANDROID ) || defined( BT_WINDOWS ) || defined( BT_LINUX )

// Include C++ memory
#include <memory>

template <typename T>
using bt_sptr = std::shared_ptr<T>;

template <typename T>
using bt_wptr = std::weak_ptr<T>;

template <typename T>
using bt_uptr = std::unique_ptr<T>;

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    // -----------------------------------------------------------

    /**
     * @brief
     * Memory - utility-class to handle memory-related logic (pointers, allocators).
     *
     * @version 0.1
    **/
    class BT_API Memory
    {

        // -----------------------------------------------------------

        // ===========================================================
        // META
        // ===========================================================

        BT_CLASS

        // -----------------------------------------------------------

    public:

        // -----------------------------------------------------------

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        template <typename T>
        static T* GetRawPointer(bt_sptr<T>& pObject)
        {
            T& object_ref = *(pObject);
            return &object_ref;
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        /**
         * @brief
         * Make shared pointer for new object.
         *
         * @thread_safety - not required.
         * @param pArgs - constructor-arguments.
         * @return - shared-pointer.
         * @throws - can throw exception.
        **/
        template <typename T, typename... _Types>
        static bt_sptr<T> MakeShared( _Types&& ... _Args )
        { return std::make_shared<T>( std::forward<_Types>(_Args)... ); }

        template <class _Tp>
        static typename std::remove_reference<_Tp>::type&& MoveShared(_Tp&& __t)
        { return std::move<_Tp>(__t); }

        template <class _Tp>
        static typename std::remove_reference<_Tp>::type&& MoveWeak(_Tp&& __t)
        { return std::move<_Tp>(__t); }

        template <class T>
        static std::weak_ptr<T> MakeWeak( bt_sptr<T>& pShared )
        { return std::weak_ptr<T>( pShared ); }

        template <typename T, typename U>
        static bt_sptr<T> StaticCast( bt_sptr<U> pSource )
        {
            return StaticCast<T, U>( pSource );
        }

        template <typename T, typename U>
        static bt_sptr<T> DynamicCast( bt_sptr<U>& pSource )
        { return std::dynamic_pointer_cast<T, U>( pSource ); }

        // -----------------------------------------------------------

    }; /// bt::memory

    // -----------------------------------------------------------

} /// bt

using bt_Memory = bt::Memory;

#define bt_Shared bt_Memory::MakeShared
#define bt_Weak bt_Memory::MakeWeak
#define bt_SharedCast bt_Memory::StaticCast
#define bt_New new
#define bt_Delete delete

// -----------------------------------------------------------

#else
#error "bt_memory.hpp - platform not detected, configuration required."
#endif
// PLATFORM


#endif // !BT_CFG_MEMORY_HPP
