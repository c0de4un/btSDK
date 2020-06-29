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

#ifndef BT_ANDROID_I_NATIVE_HXX
#define BT_ANDROID_I_NATIVE_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================



// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        /**
         * IAndroidNative - interface to handle request to Android.
         *
         * @version 1.0
         * @authors Denis Z. (code4un@yandex.ru)
         * @since 21.03.2019
         */
        class IAndroidNative
        {

        public:

            // --------------------------------------------------------

            // ===========================================================
            // Methods
            // ===========================================================

            /**
             * Called to notify Android about Error.
             *
             * @thread_safety - thread-safe, a
             * @param pCode - Error-Code. Value copied.
             * @param pException - Exception. Can be null. Value copied.
             * @throws - no exceptions thrown.
             */
            virtual void onError( const int pCode, const std::exception& pException ) = 0;

            /**
             * Called to request Stop (Exit) from Android.
             *
             * @thread_safety - thread-safe, atomics used.
             * @throws - no exceptions thrown.
             */
            virtual void onStopRequest() = 0;

            // --------------------------------------------------------

        }; /// bt::android::IAndroidNative

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_IAndroidNative = bt::android::IAndroidNative;

#define BT_ANDROID_I_NATIVE_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_I_NATIVE_HXX
