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

#ifndef BT_ANDROID_APPLICATION_HPP
#define BT_ANDROID_APPLICATION_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::Application
#ifndef BT_CORE_APPLICATION_HPP
#include "../../core/app/Application.hpp"
#endif // !BT_CORE_APPLICATION_HPP

// Include bt::android::IAndroidNative
#ifndef BT_ANDROID_I_NATIVE_HXX
#include "../jni/IAndroidNative.hxx"
#endif // !BT_ANDROID_I_NATIVE_HXX

// Include bt::android::AndroidJNIParams
#ifndef BT_ANDROID_JNI_PARAMS_HPP
#include "../jni/AndroidJNIParams.hpp"
#endif // !BT_ANDROID_JNI_PARAMS_HPP

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

// Include jni.h from NDK
#include <jni.h>

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
         * AndroidApp - adapter/wrapper for Application of btEngine & Android-Application API.
         *
         * @version 0.1
        **/
        BT_API class AndroidApp final : public bt_App, public bt_IAndroidNative
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_CLASS

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // TYPES
            // ===========================================================

            /**
             * @brief
             * AndroidAppArgs - struct. to transfer collection of params,
             * like globals limit or Java/Kotlin class.
             *
             * @version 0.1
            **/
            struct BT_API AndroidAppArgs final : public bt_AppParams
            {

                // -----------------------------------------------------------

                // ===========================================================
                // META
                // ===========================================================

                BT_STRUCT

                // ===========================================================
                // CONSTRUCTOR & DESTRUCTOR
                // ===========================================================

                /**
                 * @brief
                 * AndroidAppArgs constructor.
                 *
                 * @throws - no exceptions.
                **/
                explicit AndroidAppArgs() noexcept
                    : AppParams()
                {
                }

                /**
                 * @brief
                 * AndroidAppArgs destructor.
                 *
                 * @throws - no exceptions.
                **/
                virtual ~AndroidAppArgs() noexcept = default;

                // -----------------------------------------------------------

            }; /// bt::android::AndroidAppArgs

            // -----------------------------------------------------------

        private:

            // -----------------------------------------------------------

            // ===========================================================
            // DELETED
            // ===========================================================

            AndroidApp(const AndroidApp&) = delete;
            AndroidApp& operator=(const AndroidApp&) = delete;
            AndroidApp(AndroidApp&&) = delete;
            AndroidApp& operator=(AndroidApp&&) = delete;

            // -----------------------------------------------------------

        protected:

            // -----------------------------------------------------------

            // ===========================================================
            // bt::core::Application
            // ===========================================================

            /**
             * @brief
             * Called on Termination of an instance.
             *
             * @thread_safety - instance thread-lock used.
             * @throws - no exceptions.
            **/
            virtual void onTerminate() BT_NOEXCEPT final;

            /**
             * @brief
             * Called when System starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() final;

            /**
             * @brief
             * Called whe System resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() final;

            /**
             * @brief
             * Called whe System pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() final;

            /**
             * @brief
             * Called whe System stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() final;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AndroidApp constructor.
             *
             * @param pArgs - Android App Arguments.
            **/
            explicit AndroidApp( const AndroidAppArgs& pArgs );

            /**
             * @brief
             * AndroidApp destructor.
             *
             * @throws - can throw exception:
             *           - mutex;
             *           - null;
            **/
            virtual ~AndroidApp();

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Send Stop-Request to the Activity.
             *
             * @thread_safety - not thread-safe.
             * @param jniEnv - JNI-Environment. Null for default.
             * @param pCaller - Calling class (Java/Kotlin Class/Object).
            **/
            static BT_API void StopActivity( JNIEnv* jniEnv );

            /**
             * @brief
             * Send Error-Message to the Activity.
             *
             * @thread_safety - not thread-safe.
             * @param jniEnv - JNI-Environment. Null for default.
             * @param pMsg - message.
             * @param pCaller - Calling class (Java/Kotlin Class/Object).
            **/
            static BT_API void ActivityError( JNIEnv* jniEnv, const char* const pMsg );

            // ===========================================================
            // bt::android::IAndroidNative
            // ===========================================================

            /**
             * Called to notify Android about Error.
             *
             * @thread_safety - thread-safe, a
             * @param pCode - Error-Code. Value copied.
             * @param pException - Exception. Can be null. Value copied.
             * @throws - no exceptions thrown.
             */
            virtual void onError( const int pCode, const std::exception& pException ) final;

            /**
             * Called to request Stop (Exit) from Android.
             *
             * @thread_safety - thread-safe, atomics used.
             * @throws - no exceptions thrown.
             */
            virtual void onStopRequest() final;

            // -----------------------------------------------------------

        }; /// bt::android::AndroidApp

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_AndroidApp = bt::android::AndroidApp;
using bt_AndroidAppArgs = bt::android::AndroidApp::AndroidAppArgs;

#define BT_ANDROID_APPLICATION_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_APPLICATION_HPP
