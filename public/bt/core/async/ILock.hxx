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

#ifndef BT_CORE_I_LOCK_HXX
#define BT_CORE_I_LOCK_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare bt::core::IMutex
#ifndef BT_CORE_I_MUTEX_DECL
#define BT_CORE_I_MUTEX_DECL
namespace bt { namespace core { class IMutex; } }
using bt_IMutex = bt::core::IMutex;
#endif // !BT_CORE_I_MUTEX_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * ILock - thread-lock intarface.
         *
         * @version 0.1
         * @authors Denis Z. (code4un@yandex.ru)
        **/
        class BT_API ILock
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_INTERFACE

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * ILock destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~ILock() BT_NOEXCEPT
            {
            }

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Check if this lock is locked.
             *
             * @thread_safety - thread-safe (atomic, not thread-lock).
             * @throws - no exceptions.
            **/
            virtual bool isLocked() const BT_NOEXCEPT = 0;

            /**
             * @brief
             * Returns lock.
             *
             * @thread_safety - not thread-safe.
             * @throws - no exceptions.
            **/
            virtual bt_IMutex* getMutex() BT_NOEXCEPT = 0;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Tries to lock this lock.
             *
             * @thread_safety - thread-safe (atomic, not thread-lock).
             * @returns - 'true' if locked, 'false' if failed.
             * @throws - (!) no exceptions
            **/
            virtual bool try_lock( bt_IMutex* const pMutex = nullptr ) BT_NOEXCEPT = 0;

            /**
             * @brief
             * Lock this lock.
             *
             * @thread_safety - thread-safe (atomic, no locks).
             * @throws - can throw exception (self-lock, etc).
            **/
            virtual void lock( bt_IMutex* const pMutex = nullptr ) = 0;

            /**
             * @brief
             * Unlock this lock.
             *
             * @thread_safety - thread-safe (atomics, no locks).
             * @throws - no exceptions.
            **/
            virtual void unlock() BT_NOEXCEPT = 0;

            // -----------------------------------------------------------

        }; /// bt::core::ILock

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_ILock = bt::core::ILock;
#define BT_CORE_I_LOCK_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_I_LOCK_HXX
