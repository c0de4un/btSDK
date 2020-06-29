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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_ANDROID_APPLICATION_HPP
#include "../../../public/bt/android/app/AndroidApp.hpp"
#endif // !BT_ANDROID_APPLICATION_HPP

// Include bt::android::AndroidJNIAdapter
#ifndef BT_ANDROID_JNI_ADAPTER_HPP
#include "../../../../public/bt/android/jni/AndroidJNIAdapter.hpp"
#endif // !BT_ANDROID_JNI_ADAPTER_HPP

// Include bt::android::AndroidJNICache
#ifndef BT_ANDROID_JNI_CACHE_HPP
#include "../../../../public/bt/android/jni/AndroidJNICache.hpp"
#endif // !BT_ANDROID_JNI_CACHE_HPP

// Include bt::java::JNICache
#ifndef BT_JAVA_JNI_CACHE_HPP
#include "../../../../public/bt/java/jni/JNICache.hpp"
#endif // !BT_JAVA_JNI_CACHE_HPP

// Include bt::java::JNIAdapter
#ifndef BT_JAVA_JNI_ADAPTER_HPP
#include "../../../../public/bt/java/jni/JNIAdapter.hpp"
#endif // !BT_JAVA_JNI_ADAPTER_HPP

// DEBUG
#if defined( BT_DEBUG ) || defined( DEBUG )

// Include bt::log
#ifndef BT_CFG_LOG_HPP
#include "../../../../public/bt/cfg/bt_log.hpp"
#endif // !BT_CFG_LOG_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../../../public/bt/cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

// Include bt::assert
#ifndef BT_CFG_ASSERT_HPP
#include "../../../../public/bt/cfg/bt_assert.hpp"
#endif // !BT_CFG_ASSERT_HPP

#endif
// DEBUG

// ===========================================================
// bt::android::AndroidApp
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        AndroidApp::AndroidApp( const AndroidAppArgs& pArgs )
            : Application(pArgs)
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp constructed", bt_ELogLevel::Info );
#endif // DEBUG
        }

        AndroidApp::~AndroidApp()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp destroyed", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // bt::core::Application
        // ===========================================================

        void AndroidApp::onTerminate() BT_NOEXCEPT
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onTerminate", bt_ELogLevel::Info );
#endif // DEBUG

            // Terminate AndroidJNIAdapter
            bt_JNIAdapter::Terminate();

            // Terminate AndroidJNICache
            bt_JNICache::Terminate();

            Application::onTerminate();
        }

        bool AndroidApp::onStart()
        {// @TODO AndroidApp::onStart
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onStart", bt_ELogLevel::Info );
#endif // DEBUG
            return true;// @TODO For ActivityStop Test
            //return Application::onStart();
        }

        bool AndroidApp::onResume()
        {// @TODO AndroidApp::onResume
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onResume", bt_ELogLevel::Info );
#endif // DEBUG

            return Application::onResume();
        }

        void AndroidApp::onPause()
        {// @TODO AndroidApp::onPause
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onPause", bt_ELogLevel::Info );
#endif // DEBUG

            Application::onPause();
        }

        void AndroidApp::onStop()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onStop", bt_ELogLevel::Info );
#endif // DEBUG

            // Stop AndroidActivity
            StopActivity( nullptr );

            Application::onStop();
        }

        // ===========================================================
        // METHODS
        // ===========================================================

        BT_API void AndroidApp::StopActivity( JNIEnv* jniEnv )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::StopActivity", bt_ELogLevel::Info );
#endif // DEBUG

            // Get AndroidJNICache
            bt_sptr<bt_AndroidJNICache> jniCache = bt_Memory::StaticCast<bt_AndroidJNICache, bt_IJNICache>( bt_JNICache::getInstance() );

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( jniCache != nullptr && "AndroidApp::StopActivity - JNICache is null !" );
#else // !DEBUG
            if ( jniCache == nullptr )
                return;
#endif // DEBUG

            // Get AndroidJNIParams
            const bt_AJNIParams& jniParams = jniCache->mParams;

            // Get JNIEnv
            if ( jniEnv == nullptr )
                jniEnv = jniCache->getJNIEnv( jniParams.mRenderThreadName );

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( jniEnv && "AndroidApp::StopActivity - JNIEnv is null. Can't automatically detect default JNIEnv instance." );
                    bt_assert( !jniParams.mRenderThreadName.empty() && "AndroidApp::StopActivity - Render-thread name not set." );
#else // !DEBUG
            if ( jniEnv == nullptr )
                return;
#endif // DEBUG

            // Get Java/Kotlin class,
            jclass jClazz_ = jniEnv->FindClass( jniParams.mClassName.c_str() );

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( jClazz_ != nullptr && "AndroidApp::StopActivity - jclass not found !" );
            bt_assert( !jniParams.mStopMethod.empty() && "AndroidApp::StopActivity - Stop method name not set." );
#else
            if ( jClazz_ == nullptr )
                return;
#endif // DEBUG

            // Get Method.
            jmethodID jMethodID_ = jniEnv->GetStaticMethodID( jClazz_, jniParams.mStopMethod.c_str(), "()V" );

#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_assert( jMethodID_ != nullptr && "AndroidApp::StopActivity - jmethodID not found !" );
#else
            if ( jMethodID_ == nullptr )
                return;
#endif // DEBUG

            // Send Stop request to Activity or other Android Entity.
            jniEnv->CallStaticVoidMethod( jClazz_, jMethodID_ );
        }

        BT_API void AndroidApp::ActivityError( JNIEnv* jniEnv, const char* const pMsg )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::ActivityError", bt_ELogLevel::Info );
#endif // DEBUG

            // Stop
            StopActivity( jniEnv );
        }

        // ===========================================================
        // bt::android::IAndroidNative
        // ===========================================================

        void AndroidApp::onError( const int pCode, const std::exception& pException )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onError", bt_ELogLevel::Error );
#endif // DEBUG

            // Stop
            StopActivity( nullptr );
        }

        void AndroidApp::onStopRequest()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidApp::onStopRequest", bt_ELogLevel::Info );
#endif // DEBUG

            // Stop
            StopActivity( nullptr );
        }

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

// -----------------------------------------------------------
