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

#ifndef BT_CORE_MUTEX_HPP
#define BT_CORE_MUTEX_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::IMutex
#ifndef BT_CORE_I_MUTEX_HXX
#include "IMutex.hxx"
#endif // !BT_CORE_I_MUTEX_HXX

// Include bt::atomic
#ifndef BT_CFG_ATOMIC_HPP
#include "../../cfg/bt_atomic.hpp"
#endif // !BT_CFG_ATOMIC_HPP

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
         * Mutex - base mutex class.
         *
         * @version 0.1
        **/
        class BT_API Mutex// : public bt_IMutex
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

            /** Locked-flag. **/
            bt_atomic<bool> mLockedFlag;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Mutex constructor.
             *
             * @throws - no exceptions.
            **/
            explicit Mutex();

            // ===========================================================
            // DELETED
            // ===========================================================

            Mutex(const Mutex&) = delete;
            Mutex& operator=(const Mutex&) = delete;
            Mutex(Mutex&&) = delete;
            Mutex& operator=(Mutex&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Mutex destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~Mutex();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Check if this mutex is locked.
             *
             * @thread_safety - thread-safe (atomic, not thread-lock).
             * @throws - no exceptions.
            **/
            virtual bool isLocked() const BT_NOEXCEPT final;

            // -----------------------------------------------------------

        }; /// bt::core::Mutex

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------

#endif // !BT_CORE_MUTEX_HPP
