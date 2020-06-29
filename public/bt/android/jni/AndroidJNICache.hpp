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

#ifndef BT_ANDROID_JNI_CACHE_HPP
#define BT_ANDROID_JNI_CACHE_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::java::IJNICache
#ifndef BT_JAVA_I_JNI_CACHE_HXX
#include "../../java/jni/IJNICache.hxx"
#endif // !BT_JAVA_I_JNI_CACHE_HXX

// Include bt::mutex
#ifndef BT_CFG_MUTEX_HPP
#include "../../cfg/bt_mutex.hpp"
#endif // !BT_CFG_MUTEX_HPP

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

// Include bt::map
#ifndef BT_CFG_MAP_HPP
#include "../../cfg/bt_map.hpp"
#endif // !BT_CFG_MAP_HPP

// Include bt::androidAndroidJNIParams
#ifndef BT_ANDROID_JNI_PARAMS_HPP
#include "AndroidJNIParams.hpp"
#endif // !BT_ANDROID_JNI_PARAMS_HPP

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

        /**
         * @brief
         * AndroidJNICache - JNI-specific objects cache managing class for Android API.
         *
         * @version 0.1
        **/
        class BT_API AndroidJNICache final : public bt_IJNICache
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

            /** AAssetManager **/
            AAssetManager* mAAssetManager;

            /** Mutex. **/
            mutable bt_Mutex mAssetsManagerMutex;

            /** JNI Environments **/
            bt_map<const bt_String, JNIEnv*> mJNIEnvs;

            /** Environments Mutex. **/
            mutable bt_Mutex mEnvMutex;

            /** JNI Objects **/
            bt_map<const bt_String, jobject> mObjects;

            /** Objects Mutex. **/
            mutable bt_Mutex mObjectsMutex;

            // ===========================================================
            // DELETED
            // ===========================================================

            AndroidJNICache(const AndroidJNICache&) = delete;
            AndroidJNICache& operator=(const AndroidJNICache&) = delete;
            AndroidJNICache(AndroidJNICache&&) = delete;
            AndroidJNICache& operator=(AndroidJNICache&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTANTS
            // ===========================================================

            /** Android JNI Params. **/
            const bt_AJNIParams mParams;

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AndroidJNICache constructor.
             *
             * @param jniParams - Android JNI-specific params (globals limit, activity class name, etc).
             * @throws - can throw exception.
            **/
            explicit AndroidJNICache( const bt_AJNIParams& jniParams );

            /**
             * @brief
             * AndroidJNICache destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~AndroidJNICache();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * Sets AAssetManager pointer-value.
             *
             * (!) This method calls JNIEnv->NewGlobalRef(assetManager)
             * (!) Associated with AAssetManager jobject automatically deleted
             * in #clear( ) method.
             *
             * @thread_safety - not thread-safe.
             * @param assetManagerObject - jobject to cache.
             * @param jniEnv - JNIEnv. Any thread can be used, because AAssetManager doesn't depends
             * on thread, unlikely JNIEnv. Null if 'Global Reference' already created.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            void setAAssetManager( jobject jAssetManager, JNIEnv *const jniEnv );

            /**
             * Returns AAssetManager.
             *
             * @thread_safety - not thread-safe.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            AAssetManager * getAAssetManager( ) const;

            // ===========================================================
            // IJNICache
            // ===========================================================

            /**
             * Search for JNIEnv with given key.
             *
             * @thread_safety - thread-lock used.
             * @param pName - key associated with JNIEnv. Usually it's thread-name.
             * @return - JNIEnv or null.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual JNIEnv * getJNIEnv( const bt_String& pName ) final;

            /**
             * Returns jobject, or null.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - associated key ( example: 'my_thread asset' ).
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual jobject * getObject( const bt_String& pName ) final;

            /**
             * Add JNIEnv to cache.
             *
             * (?) All JNIEnvs deleted in #clear() method.
             *
             * @thread_safety - thread-lock used.
             * @param pName - associated key (thread name).
             * @param jniEnv - JNIEnv.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual void addJNIEnv( const bt_String& pName, JNIEnv *const jniEnv ) final;

            /**
             * Removes JNIEnv from cache.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - Associated thread-name.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual void removeJNIEnv( const bt_String& pName ) final;

            /**
             * Add jobject.
             *
             * (!) Use JNIEnv->NewGlobalReference(jobject) before this.
             * (?) All jobjects deleted in #clear() method.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - Key. Used to find this jobject later. ! Recommends to put
             * thread name as first, then after space (' ') or # name of object !. Caller must delete manually given value !
             * @param pObject - jobject.
             * @param jniEnv - JNIEnv used to create new 'Global Reference', null if already done.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual void addObject( const bt_String& pName, jobject & pObject, JNIEnv *const jniEnv ) final;

            /**
             * Remove jobject from cache.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - associated key ( example: 'my_thread asset' ).
             * @param jniEnv - JNIEnv used to create new 'Global Reference' for jobject.
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual void removeObject( const bt_String& pName, JNIEnv *const jniEnv ) final;

            /**
             * Clear JNICache.
             * Removes all jobjects, AAssetManager, JNIEnvs, etc.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param jniEnv - JNIEnv used to delete 'Global Reference'.
             * If null, default used (first added).
             * @throws - can throw exception:
             *           - mutex;
             *           - nullptr;
             */
            virtual void clear( JNIEnv * jniEnv ) final;

            // -----------------------------------------------------------

        }; /// bt::android::AndroidJNICache

    } /// bt::core

} /// bt

using bt_AndroidJNICache = bt::android::AndroidJNICache;
#define BT_ANDROID_JNI_CACHE_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_JNI_CACHE_HPP
