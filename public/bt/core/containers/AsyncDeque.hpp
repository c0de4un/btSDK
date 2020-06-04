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

#ifndef BT_CORE_ASYNC_DEQUE_HPP
#define BT_CORE_ASYNC_DEQUE_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::queue
#ifndef BT_CFG_QUEUE_HPP
#include "../../cfg/bt_queue.hpp"
#endif // !BT_CFG_QUEUE_HPP

// Include bt:atomic
#ifndef BT_CFG_ATOMIC_HPP
#include "../../cfg/bt_atomic.hpp"
#endif // !BT_CFG_ATOMIC_HPP

// Include bt::mutex
#ifndef BT_CFG_MUTEX_HPP
#include "../../cfg/bt_mutex.hpp"
#endif // !BT_CFG_MUTEX_HPP

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
         * AsyncDeque - deque container with thread-safety.
         *
         * @version 0.1
        **/
        template <typename T>
        class BT_API AsyncDeque
        {// @TODO AsyncDeque

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_CLASS

            // -----------------------------------------------------------

        private:

            // -----------------------------------------------------------

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Mutex. **/
            mutable bt_Mutex mMutex;

            /** Elements counter. **/
            bt_atomic<bt_size_t> mElementsCount;

            /** Deque **/
            bt_deque<T> mDeque;

            // ===========================================================
            // DELETED
            // ===========================================================

            AsyncDeque(const AsyncDeque&) = delete;
            AsyncDeque& operator=(const AsyncDeque&) = delete;
            AsyncDeque(AsyncDeque&&) = delete;
            AsyncDeque& operator=(AsyncDeque&&) = delete;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Updates elements counter.
             *
             * @thread_safety - thread-lock used.
             * @throws - no exceptions.
            **/
            inline void updateElementsCount() noexcept
            { mElementsCount = mDeque.size(); }

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AsyncDeque constructor.
             *
             * @throws - can throw exception.
            **/
            explicit AsyncDeque( )
                : mMutex(),
                mElementsCount(0),
                mDeque( )
            {
            }

            /**
             * @brief
             * AsyncDeque destructor.
             *
             * @throws - can throw exception.
            **/
            ~AsyncDeque() = default;

            // ===========================================================
            // METHODS
            // ===========================================================

            bool isEmpty() const
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.empty();
            }

            bt_size_t Count() const
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.size();
            }

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Push Front.
             *
             * @thread_safety - thread-lock used.
             * @param pItem - Item.
             * @throws - can throw exception.
            **/
            void PushFront( T& pItem )
            {
                bt_SpinLock lock( &mMutex );
                mDeque.push_front( pItem );
            }

            /**
             * @brief
             * Push Back.
             *
             * @thread_safety - thread-lock used.
             * @param pItem - Item.
             * @throws - can throw exception.
            **/
            void PushBack( T& pItem )
            {
                bt_SpinLock lock( &mMutex );
                mDeque.push_back( pItem );
            }

            /**
             * @brief
             * Remove Last element.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            void PopBack()
            {
                bt_SpinLock lock( &mMutex );
                mDeque.pop_back();
            }

            /**
             * @brief
             * Remove Last element.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            void PopFront()
            {
                bt_SpinLock lock( &mMutex );
                mDeque.pop_front();
            }

            /**
             * @brief
             * Get First element.
             *
             * (!) Be careful & use #isEmpty or # before.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            T& Front( )
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.front();
            }

            /**
             * @brief
             * Get First element.
             *
             * (!) Be careful & use #isEmpty or # before.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            T& Front( ) const
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.front();
            }

            /**
             * @brief
             * Get Last element.
             *
             * (!) Be careful & use #isEmpty or # before.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            T& Back( )
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.back();
            }

            /**
             * @brief
             * Get Last element.
             *
             * (!) Be careful & use #isEmpty or # before.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            T& Back( ) const
            {
                bt_SpinLock lock( &mMutex );
                return mDeque.back();
            }

            // -----------------------------------------------------------

        }; /// bt::core::AsyncDeque

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

#define BT_CORE_ASYNC_DEQUE_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ASYNC_DEQUE_HPP
