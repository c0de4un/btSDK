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

#ifndef BT_CORE_ID_VECTOR_HPP
#define BT_CORE_ID_VECTOR_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::vector
#ifndef BT_CFG_VECTOR_HPP
#include "../../cfg/bt_vector.hpp"
#endif // !BT_CFG_VECTOR_HPP

// Include bt::map
#ifndef BT_CFG_MAP_HPP
#include "../../cfg/bt_map.hpp"
#endif // !BT_CFG_MAP_HPP

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
         * IDVector - linear container for numeric values.
         *
         * @thread_safety - thread-lock used.
         *
         * @version 0.1
        **/
        template <typename T>
        class BT_API IDVector final
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

            /** Available IDs **/
            bt_map<T, bool> mIDs;

            /** Mutex. **/
            bt_Mutex mMutex;

            // ===========================================================
            // DELETED
            // ===========================================================

            IDVector(const IDVector&) = delete;
            IDVector& operator=(const IDVector&) = delete;
            IDVector(IDVector&&) = delete;
            IDVector& operator=(IDVector&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * IDVector constructor.
             *
             * @throws - can throw exception.
            **/
            explicit IDVector()
                : mIDs(),
                mMutex()
            {
            }

            /**
             * @brief
             * IDVector destructor.
             *
             * @throws - can throw exception.
            **/
            ~IDVector() = default;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns available ID.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            T getAvailable()
            {
                bt_SpinLock lock( &mMutex );

                auto pos = mIDs.begin();
                auto end = mIDs.cend();

                while( pos != end )
                {
                    if (!pos->second)
                    {
                        pos->second = true;
                        return pos->first;
                    }
                    pos++;
                }

                const T newId = (T)mIDs.size() + 1;
                mIDs[(size_t)newId] = true;
                return newId;
            }
            
            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Returns ID for reusage.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            void release( T pID )
            {
                bt_SpinLock lock(&mMutex);
                mIDs[pID] = false;
            }
            
            // -----------------------------------------------------------

        }; /// bt::core::IDVector

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template <typename T>
using bt_IDVector = bt::core::IDVector<T>;

#define BT_CORE_ID_VECTOR_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ID_VECTOR_HPP
