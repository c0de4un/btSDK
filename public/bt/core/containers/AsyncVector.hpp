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

#ifndef BT_CORE_ASYNC_VECTOR_HPP
#define BT_CORE_ASYNC_VECTOR_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::vector
#ifndef BT_CFG_VECTOR_HPP
#include "../../cfg/bt_vector.hpp"
#endif // !BT_CFG_VECTOR_HPP

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
         * AsyncVector - vector container with thread-safety.
         *
         * @version 0.1
        **/
        template <typename T>
        class BT_API AsyncVector
        {

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
            bt_Mutex mMutex;

            /** Vector. **/
            bt_vector<T> mVector;

            // ===========================================================
            // DELETED
            // ===========================================================

            AsyncVector(const AsyncVector&) = delete;
            AsyncVector& operator=(const AsyncVector&) = delete;
            AsyncVector(AsyncVector&&) = delete;
            AsyncVector& operator=(AsyncVector&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTORS
            // ===========================================================

            /**
             * @brief
             * AsyncVector constructor.
             *
             * @param pCapacity - initial capacity. 0 for default.
             * @throws - can throw exception.
            **/
            explicit AsyncVector( const bt_size_t pCapacity = 0 )
                    : mMutex(),
                      mVector()
            {
                if ( pCapacity > 0 )
                    mVector.reserve(pCapacity);
            }

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AsyncVector destructor.
             *
             * @throws - can throw exception.
            **/
            ~AsyncVector()
            {
            }

            // ===========================================================
            // METHODS & OPERATORS
            // ===========================================================

            /**
             * @brief
             * Reserve
             *
             * @thread_safety - thread-lock used.
             * @param pCapacity - new capacity.
             * @throws - can throw exception.
            **/
            void Reserve( const bt_size_t pCapacity )
            {
                bt_SpinLock lock(&mMutex);
                mVector.reserve();
            }

            /**
             * @brief
             * Add item to the end.
             *
             * @thread_safety - thread-lock used.
             * @param pItem - item.
             * @throws - can throw exception.
            **/
            void Push( T& pItem )
            {
                bt_SpinLock lock(&mMutex);
                mVector.push_back( pItem );
            }

            /**
             * @brief
             * Remove last item.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            void PopBack()
            {
                mVector.pop_back();
            }

            /**
             * @brief
             * Search item.
             *
             * @thread_safety - thread-lock used.
             * @param pOutput - index output.
             * @return - true if found.
             * @throws - can throw exception.
            **/
            bool Find( const T& pItem, bt_size_t *const pOutput)
            { return bt_VectorUtil<T>::Find( mVector, pItem, pOutput ); }

            /**
             * @brief
             * Returns item by index.
             *
             * @thread_safety - thread-lock used.
             * @param pIdx - index.
             * @throws - can throw exception.
            **/
            T& Get(const bt_size_t pIdx)
            {
#if defined( BT_DEBUG ) // DEBUG
                bt_assert( pIdx < mVector.size() && "AsyncVector::Get - Out-of-range." );
#endif // DEBUG

                return mVector.at(pIdx);
            }

            /**
             * @brief
             * Remove element.
             *
             * @thread_safety - thread-lock used.
             * @param pIdx - index.
             * @param pSwap - true to avoid reallocation, but break elements order.
             * @throws - can throw exception.
            **/
            void Erase(const bt_size_t pIdx, const bool pSwap = false)
            {
#if defined( BT_DEBUG ) // DEBUG
                bt_assert(pIdx < mVector.size() && "AsyncVector::Erase - Out-of-range.");
#endif // DEBUG

                if ( pSwap )
                    bt_VectorUtil<T>::SwapPopByIdx( mVector, pIdx );
                else
                    mVector.erase(mVector.begin() + pIdx);
            }

            /**
             * @brief
             * Remove element.
             *
             * @thread_safety - thread-lock used.
             * @param pItem - element.
             * @param pSwap - true to avoid reallocation, but break elements order.
             * @throws - can throw exception.
            **/
            void Erase( const T& pItem, const bool pSwap = false)
            {
                if ( pSwap )
                    bt_VectorUtil<T>::SwapPopBy(mVector, pItem);
                else
                    mVector.erase(pItem);
            }

            T& operator[](const bt_size_t pIdx)
            {
#if defined( BT_DEBUG ) // DEBUG
                bt_assert(pIdx < mVector.size() && "AsyncVector::[] - Out-of-range.");
#endif // DEBUG

                return mVector[pIdx];
            }

            // -----------------------------------------------------------

        }; /// bt::core::AsyncVector

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template <typename T>
using bt_AsyncVector = bt::core::AsyncVector<T>;

#define BT_CORE_ASYNC_VECTOR_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ASYNC_VECTOR_HPP
