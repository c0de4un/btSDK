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

#ifndef BT_CORE_ASYNC_MAP_HPP
#define BT_CORE_ASYNC_MAP_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::map
#ifndef BT_CFG_MAP_HPP
#include "../../cfg/bt_map.hpp"
#endif // !BT_CFG_MAP_HPP

// Include bt:atomic
#ifndef BT_CFG_ATOMIC_HPP
#include "../../cfg/bt_atomic.hpp"
#endif // !BT_CFG_ATOMIC_HPP

// Include bt::mutex
#ifndef BT_CFG_MUTEX_HPP
#include "../../cfg/bt_mutex.hpp"
#endif // !BT_CFG_MUTEX_HPP

// Include bt::core::IMapIterator
#ifndef BT_CORE_I_MAP_ITERATOR_HXX
#include "IMapIterator.hxx"
#endif // !BT_CORE_I_MAP_ITERATOR_HXX

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
         * AsyncMap - map container with thread-safety.
         *
         * @version 0.1
        **/
        template <typename K = unsigned int, typename V = unsigned long>
        class BT_API AsyncMap final
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

            /** Map. **/
            bt_map<K, V> mMap;

            /** Elements counter. **/
            bt_atomic<bt_size_t> mElementsCount;

            // ===========================================================
            // DELETED
            // ===========================================================

            AsyncMap(const AsyncMap&) = delete;
            AsyncMap& operator=(const AsyncMap&) = delete;
            AsyncMap(AsyncMap&&) = delete;
            AsyncMap& operator=(AsyncMap&&) = delete;

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
            { mElementsCount = mMap.size(); }

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTORS
            // ===========================================================

            /**
             * @brief
             * AsyncMap constructor.
            **/
            explicit AsyncMap( )
                    : mMutex(),
                      mMap(),
                      mElementsCount( 0 )
            {
            }

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AsyncMap destructor.
             *
            **/
            ~AsyncMap()
            {
            }

            // ===========================================================
            // METHODS & OPERATORS
            // ===========================================================

            /**
             * @brief
             * Returns number of elements.
             *
             * @thread_safety - atomics used.
             * @throws - no exceptions.
            **/
            bt_size_t Count() const noexcept
            {
                const bt_size_t result = mElementsCount;
                return result;
            }

            /**
             * @brief
             * Returns 'true' if empty
             *
             * @thread_safety - atomics used.
             * @throws - no exceptions.
            **/
            bool isEmpty() const noexcept
            { return Count() < 1; }

            /**
             * @brief
             * Iterate map to find key.
             *
             * @thread_safety - thread-lock used.
             * @param pIterator IMapIterator implementation.
             * @return - Key, or null.
             * @throws - can throw exception;
            **/
            const void* Iterate( bt_IMapIterator *const pIterator )
            {
                if (!pIterator)
                    return nullptr;

                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                auto pos = mMap.begin(); // bt_map<K, V>::iterator
                auto end = mMap.cend(); // bt_map<K, V>::const_iterator
                const void* result = nullptr;

                while( pos != end )
                {
                    auto key = pos->first;
                    auto value = pos->second;

                    if ( ( result = pIterator->onIterateMap(&key, &value) ) != nullptr)
                        return result;

                    pos++;
                }

                return nullptr;
            }

            /**
             * @brief
             * Insert element to the map.
             *
             * @thread_safety - thread-lock used.
             * @param pKey - Key.
             * @param pValue - Value.
             * @param pReplace - 'true' to replace pervious value. Allows to avid data-race.
             * @throws - can throw exception.
            **/
            void Insert( K pKey, V pValue, const bool pReplace = false )
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );

                if ( pReplace || mMap.find(pKey) == mMap.cend() )
                    mMap[pKey] = pValue;

                updateElementsCount();
            }

            /**
             * @brief
             * Remove element from the map.
             *
             * @thread_safety - thread-lock used.
             * @param pKey - Key.
             * @param pValue - Value.
             * @throws - can throw exception.
            **/
            void Erase( K pKey )
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                mMap.erase( pKey );

                updateElementsCount();
            }

            /**
             * @brief
             * Clear map.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            void Clear()
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                mMap.clear();

                updateElementsCount();
            }

            /**
             * @brief
             * Check if item is stored.
             *
             * @thread_safety - thread-lock used.
             * @param pKey - Key.
             * @return - true if found.
             * @throws - can throw exception.
            **/
            bool Contains( K pKey )
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                return mMap.find(pKey) != mMap.cend();
            }

            /**
             * @brief
             * [] operator alias.
             *
             * @thread_safety - thread-lock used.
             * @param pKey - Key.
             * @throws - can throw exception.
            **/
            V& Get( K pKey )
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                return mMap[pKey];
            }

            /**
             * @brief
             * [] operator to access map by key.
             *
             * @thread_safety - thread-lock used.
             * @param pKey - Key.
             * @return - Value.
             * @throws - can throw exception.
            **/
            V& operator[]( K pKey )
            {
                bt_SpinLock lock( static_cast<bt_IMutex*>(&mMutex) );
                return mMap[pKey];
            }

            // -----------------------------------------------------------

        }; /// bt::core::AsyncMap

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template <typename K, typename V>
using bt_AsyncMap = bt::core::AsyncMap<K, V>;

#define BT_CORE_ASYNC_MAP_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ASYNC_MAP_HPP
