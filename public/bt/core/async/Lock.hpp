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

#ifndef BT_CORE_LOCK_HPP
#define BT_CORE_LOCK_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::ILock
#ifndef BT_CORE_I_LOCK_HXX
#include "ILock.hxx"
#endif // !BT_CORE_I_LOCK_HXX

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
         * Lock - base lock-class.
         *
         * @version 0.1
        **/
        class BT_API Lock : public bt_ILock
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

            /** Mutex. **/
            bt_IMutex* mMutex;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Lock constructor.
             *
             * @param pMutex - mutex to store. Automatically unlocked, not deleted (instance not managed).
             * @param defferLock - 'false' to lock mutex, 'true' to delay until #lock called.
             * @throws - no exceptions.
            **/
            explicit Lock( bt_IMutex* const pMutex = nullptr, const bool defferLock = true );

            // ===========================================================
            // DELETED
            // ===========================================================

            Lock(const Lock&) = delete;
            Lock& operator=(const Lock&) = delete;
            Lock(Lock&&) = delete;
            Lock& operator=(Lock&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Lock destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~Lock() BT_NOEXCEPT;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns lock.
             *
             * @thread_safety - not thread-safe.
             * @throws - no exceptions.
            **/
            virtual bt_IMutex* getMutex() BT_NOEXCEPT final;

            // ===========================================================
            // METHODS
            // ===========================================================

            // -----------------------------------------------------------

        }; /// bt::core::Lock

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_Lock = bt::core::Lock;
#define BT_CORE_LOCK_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_LOCK_HPP
