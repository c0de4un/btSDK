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

#ifndef BT_CFG_VECTOR_HPP
#define BT_CFG_VECTOR_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::numeric
#ifndef BT_CFG_NUMERIC_HPP
#include "bt_numeric.hpp"
#endif // !BT_CFG_NUMERIC_HPP

// PLATFORM
#if defined( BT_ANDROID ) || defined( BT_WINDOWS ) || defined( BT_LINUX ) // ANDROID

// Include STL (C++) vector
#include <vector>

template <typename T>
using bt_vector = std::vector<T>;

// -----------------------------------------------------------

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * VectorUtil - utilities for vector containers.
         *
         * @version 0.1
        **/
        template<typename T>
        class BT_API VectorUtil final
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
            // CONSTRUCTOR
            // ===========================================================

            explicit VectorUtil()
            {
            }

            // ===========================================================
            // DELETED
            // ===========================================================

            VectorUtil(const VectorUtil&) = delete;
            VectorUtil& operator=(const VectorUtil&) = delete;
            VectorUtil(VectorUtil&&) = delete;
            VectorUtil& operator=(VectorUtil&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            ~VectorUtil()
            {
            }

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Search Item's index.
             *
             * @thread_safety - not thread-safe.
             * @param pVector - vector.
             * @param pItem - Item.
             * @param pOutput - output index.
             * @return - false if failed, true if found.
            **/
            static bool Find( bt_vector<T>& pVector, const T& pItem, bt_size_t *const pOutput)
            {
                auto itemsIterator = std::find(pVector.begin(), pVector.end(), pItem);

                if ( itemsIterator != pVector.cend() ) {
                    if ( pOutput != nullptr )
                        *pOutput = std::distance( pVector.begin(), itemsIterator );
                    return true;
                } else {
                    return false;
                }
            }

            /**
             * Swap & remove (erase, pop_back) the given element (item.)
             *
             * @thread_safety - not thread-safe.
             * @param T - Type of item.
             * @param pVector - vector to modify.
             * @param pItem - item to search & remove.
            **/
            static void SwapPop(bt_vector<T>& pVector, T& pItem)
            {
                // Search
                auto itemsIterator = std::find(pVector.begin(), pVector.end(), pItem);

                // Swap & Remove
                if ( itemsIterator != pVector.cend() ) {

                    // Swap & Remove
                    if ( pVector.size() > 2 ) {

                        // Swap
                        std::swap(*itemsIterator, pVector.back());

                        // Remove
                        pVector.pop_back();
                    } else // Just Remove
                        pVector.erase(itemsIterator);


                }// Swap & Remove
            }

            /**
             * Swap & remove (erase, pop_back) the given element (item.)
             *
             * @thread_safety - not thread-safe.
             * @param T - Type of item.
             * @param pVector - vector to modify.
             * @param pIdx - item index.
            **/
            static void SwapPopByIdx(bt_vector<T>& pVector, const bt_size_t pIdx)
            {
                const bt_size_t vectSize = pVector.size();

                if ( vectSize > 2 && (vectSize - 1) > pIdx ) {
                    T a = pVector[pVector.size() - 1];
                    T b = pVector[pIdx];
                    pVector[pIdx] = a;
                    pVector[vectSize - 1] = b;
                    pVector.pop_back();
                } else {
                    pVector.erase( pVector.begin() + pIdx );
                }
            }

            // -----------------------------------------------------------

        }; /// bt::core::VectorUtil

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template<typename T>
using bt_VectorUtil = bt::core::VectorUtil<T>;

// -----------------------------------------------------------

#else
#error "bt_vector.hpp - configuration required."
#endif
// PLATFORM

// ===========================================================
// CONFIG
// ===========================================================



// -----------------------------------------------------------

#endif // !BT_CFG_VECTOR_HPP
