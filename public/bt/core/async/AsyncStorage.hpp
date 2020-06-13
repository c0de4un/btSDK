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

#ifndef BT_CORE_ASYNC_STORAGE_HPP
#define BT_CORE_ASYNC_STORAGE_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

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
         * AsyncStorage - wrapper (facade) for accessing type/object instance
         * within locked/synchronized block.
         *
         * @version 0.1
        **/
        template <typename T>
        struct BT_API AsyncStorage final
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_STRUCT

            // -----------------------------------------------------------

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Item. **/
            T mItem;

            /** Mutex. **/
            bt_Mutex mMutex;

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AsyncStorage constructor.
             *
             * @throws - can throw exception.
            **/
            explicit AsyncStorage( )
                : mItem(),
                mMutex()
            {
            }

            /**
             * @brief
             * AsyncStorage destructor.
             *
             * @throws - can throw exception.
            **/
            ~AsyncStorage() = default;

            // -----------------------------------------------------------

        }; /// bt::core::AsyncStorage

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

template <typename T>
using bt_AsyncStorage = bt::core::AsyncStorage<T>;

#define BT_CORE_ASYNC_STORAGE_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ASYNC_STORAGE_HPP
