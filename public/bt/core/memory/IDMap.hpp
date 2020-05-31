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

#ifndef BT_CORE_ID_MAP_HPP
#define BT_CORE_ID_MAP_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::IDVector
#ifndef BT_CORE_ID_VECTOR_HPP
#include "IDVector.hpp"
#endif // !BT_CORE_ID_VECTOR_HPP

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
         * IDMap - associative container for sets of numeric values.
         *
         * @thread_safety - thread-lock used.
         *
         * @version 0.1
        **/
        template <typename K, typename V>
        class BT_API IDMap final
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
            // CONFIG
            // ===========================================================

            using id_vector_t = bt_IDVector<V>;

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Mutex. **/
            bt_Mutex mMutex;

            /** ID Containers. **/
            bt_map<K, id_vector_t> mIDs;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns IDs container.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            id_vector_t& getIDList(const K pKey)
            {
                bt_SpinLock lock(&mMutex);

                auto pos = mIDs.find(pKey);

                if ( pos != mIDs.cend() )
                {
                    id_vector_t& ids = pos->second;
                    return ids;
                }

                return mIDs[pKey];
            }

            // ===========================================================
            // DELETED
            // ===========================================================

            IDMap(const IDMap&) = delete;
            IDMap& operator=(const IDMap&) = delete;
            IDMap(IDMap&&) = delete;
            IDMap& operator=(IDMap&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * IDMap constructor.
             *
             * @throws - can throw exception.
            **/
            explicit IDMap()
                    : mMutex(),
                      mIDs()
            {
            }

            /**
             * @brief
             * IDMap destructor.
             *
             * @throws - can throw exception.
            **/
            ~IDMap()
            {
            }

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns available ID.
             *
             * @thread_safety - thread-lock used.
             * @param pType - ID Type.
             * @throws - can throw exception.
            **/
            V getAvailableID( const K pType )
            {
                id_vector_t& ids = getIDList(pType);
                return ids.getAvailable();
            }

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Returns available ID for reusage.
             *
             * @thread_safety - thread-lock used.
             * @param pType - ID Type.
             * @param pID - ID to return.
             * @throws - can throw exception.
            **/
            void releaseID( const K pType, const V pID )
            {
                id_vector_t& ids = getIDList(pType);
                ids.release(pID);
            }

            // -----------------------------------------------------------

        }; /// bt::core::IDMap

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template <typename K, typename V>
using bt_IDMap = bt::core::IDMap<K, V>;

#define BT_CORE_ID_MAP_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ID_MAP_HPP
