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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_CORE_SPIN_LOCK_HPP
#include "../../../../public/bt/core/async/SpinLock.hpp"
#endif // !BT_CORE_SPIN_LOCK_HPP

// Include bt::core::IMutex
#ifndef BT_CORE_I_MUTEX_HXX
#include "../../../../public/bt/core/async/IMutex.hxx"
#endif // !BT_CORE_I_MUTEX_HXX

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

#endif
// DEBUG

// ===========================================================
// bt::core::SpinLock
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        SpinLock::SpinLock(bt_IMutex* const pMutex, const bool defferLock)
                : Lock( pMutex, defferLock )
        {
#ifdef BT_DEBUG // DEBUG
            if ( !defferLock )
            {
                bt_assert(pMutex && "Lock - mutex is null !");
            }
#endif // DEBUG

            if ( !defferLock && mMutex )
                this->lock(nullptr);
        }

        /**
         * @brief
         * SpinLock destructor.
         *
         * @throws - no exceptions.
        **/
        SpinLock::~SpinLock() BT_NOEXCEPT
        {
            this->unlock();
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        bool SpinLock::isLocked() const BT_NOEXCEPT
        { return mMutex ? mMutex->isLocked() : false; }

        // ===========================================================
        // bt::core::ILock
        // ===========================================================

        bool SpinLock::try_lock(bt_IMutex* const pMutex) BT_NOEXCEPT
        {

            if ( pMutex )
            {
                mMutex->unlock();
                mMutex = pMutex;
            }

#ifdef BT_DEBUG // DEBUG
            bt_assert( mMutex && "SpinLock::try_lock - null mutex !");
#endif // DEBUG

            for ( unsigned char i = 0; i < SPIN_LIMIT; i++ )
            {
                if ( !mMutex->isLocked() )
                    break;
            }
            return mMutex->try_lock();
        }

        void SpinLock::lock(bt_IMutex* const pMutex)
        {

            if ( pMutex )
            {
                mMutex->unlock();
                mMutex = pMutex;
            }

#ifdef BT_DEBUG // DEBUG
            bt_assert(mMutex && "SpinLock::lock - null mutex !");
#endif // DEBUG

            for ( unsigned char i = 0; i < SPIN_LIMIT; i++ )
            {
                if ( !mMutex->isLocked() )
                    break;
            }
            mMutex->lock();
        }

        void SpinLock::unlock() BT_NOEXCEPT
        {
            if ( mMutex )
                mMutex->unlock();
        }
        
        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
