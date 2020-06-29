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

#ifndef BT_ANDROID_JNI_ADAPTER_HPP
#define BT_ANDROID_JNI_ADAPTER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::java::IJNIAdapter
#ifndef BT_JAVA_I_JNI_ADAPTER_HXX
#include "../../java/jni/IJNIAdapter.hxx"
#endif // !BT_JAVA_I_JNI_ADAPTER_HXX

// Include bt::android::AndroidJNIParams
#ifndef BT_ANDROID_JNI_PARAMS_HPP
#include "AndroidJNIParams.hpp"
#endif // !BT_ANDROID_JNI_PARAMS_HPP

// Include jni.h
#include <jni.h>

// Include android/asset_manager.h
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * AndroidJNIAdapter - JNI-Adapter implementation for Android API.
         *
         * @version 0.1
        **/
        class BT_API AndroidJNIAdapter final : public bt_IJNIAdapter
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

            // ===========================================================
            // DELETED
            // ===========================================================

            AndroidJNIAdapter(const AndroidJNIAdapter&) = delete;
            AndroidJNIAdapter& operator=(const AndroidJNIAdapter&) = delete;
            AndroidJNIAdapter(AndroidJNIAdapter&&) = delete;
            AndroidJNIAdapter& operator=(AndroidJNIAdapter&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AndroidJNIAdapter constructor.
             *
             * @throws - can throw exception.
            **/
            explicit AndroidJNIAdapter();

            /**
             * @brief
             * AndroidJNIAdapter destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~AndroidJNIAdapter();

            // -----------------------------------------------------------

        }; /// bt::android::AndroidJNIAdapter

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_AndroidJNI = bt::android::AndroidJNIAdapter;
#define BT_ANDROID_JNI_ADAPTER_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_JNI_ADAPTER_HPP
