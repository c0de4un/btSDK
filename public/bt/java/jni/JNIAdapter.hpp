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

#ifndef BT_JAVA_JNI_ADAPTER_HPP
#define BT_JAVA_JNI_ADAPTER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::AsyncStorage
#ifndef BT_CORE_ASYNC_STORAGE_HPP
#include "../../core/async/AsyncStorage.hpp"
#endif // !BT_CORE_ASYNC_STORAGE_HPP

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare bt::java::IJNIAdapter
#ifndef BT_JAVA_I_JNI_ADAPTER_DECL
#define BT_JAVA_I_JNI_ADAPTER_DECL
namespace bt { namespace java { class IJNIAdapter; } }
using bt_IJNIAdapter = bt::java::IJNIAdapter;
#endif // !BT_JAVA_I_JNI_ADAPTER_DECL

// Forward-Declare bt::java::IJNICache
#ifndef BT_JAVA_I_JNI_CACHE_DECL
namespace bt { namespace java { class IJNICache; } }
using bt_IJNICache = bt::java::IJNICache;
#define BT_JAVA_I_JNI_CACHE_DECL
#endif // !BT_JAVA_I_JNI_CACHE_DECL

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace java
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * JNIAdapter - factory & facade class type.
         *
         * Allows to separate JNI-Adapter implementation from user.
         * For example, user of AndroidJNIAdapter doesn't need to know about
         * jni.h, jclass, jstring etc.
         *
         * @version 0.1
        **/
        class BT_API JNIAdapter final
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
            // CONSTANTS & FIELDS
            // ===========================================================

            /** Instance Holder. **/
            static bt_AsyncStorage<bt_sptr<bt_IJNIAdapter>> mInstanceHolder;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * JNIAdapter constructor.
             *
             * @throws - no exceptions.
            **/
            explicit JNIAdapter();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns IJNIAdapter instance.
             *
             * @thread_safety - thread-locks used.
             * @throws - can throw:
             *           - mutex;
             *           - out-of-memory;
            **/
            static BT_API bt_sptr<bt_IJNIAdapter> getInstance();

            // ===========================================================
            // DELETED
            // ===========================================================

            JNIAdapter(const JNIAdapter&) = delete;
            JNIAdapter& operator=(const JNIAdapter&) = delete;
            JNIAdapter(JNIAdapter&&) = delete;
            JNIAdapter& operator=(JNIAdapter&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * JNIAdapter destructor.
             *
             * @throws - no exceptions.
            **/
            ~JNIAdapter();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns JNICache instance, or null.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception:
             *           - out-of-memory;
             *           - mutex;
            **/
            static BT_API bt_sptr<bt_IJNICache> getCache();

            /**
             * @brief
             * Returns 'true' if JNIAdapter instance already set.
             *
             * @thread_safety - thread-locks used.
             * @throws - no exceptions.
            **/
            static BT_API bool isInitialized() BT_NOEXCEPT;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize IJNIAdapter instance.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw:
             *           - mutex;
             *           - out-of-memory;
            **/
            static BT_API void Initialize( bt_sptr<bt_IJNIAdapter>& pInstance );

            /**
             * @brief
             * Terminate IJNIAdapter instance.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw:
             *           - mutex;
            **/
            static BT_API void Terminate();

            // -----------------------------------------------------------

        }; /// bt::java::JNIAdapter

        // -----------------------------------------------------------

    } /// bt::java

} /// bt

using bt_JNIAdapter = bt::java::JNIAdapter;
#define BT_JAVA_JNI_ADAPTER_DECL

// -----------------------------------------------------------

#endif // !BT_JAVA_JNI_ADAPTER_HPP
