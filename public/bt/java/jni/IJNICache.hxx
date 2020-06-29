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

#ifndef BT_JAVA_I_JNI_CACHE_HXX
#define BT_JAVA_I_JNI_CACHE_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

// Include JNI
#if defined( ANDROID ) || defined( BT_ANDROID ) // ANDROID

// Include jni.h from NDK
#include <jni.h>

#else
#error "IJNICache.hxx - configuration required."
#endif

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
         * IJNICache - interface for JNI-Cache facade-class.
         *
         * @version 0.1
        **/
        class BT_API IJNICache
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_INTERFACE

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * IJNICache destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~IJNICache() = default;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * Search for JNIEnv with given key.
             *
             * @thread_safety - thread-lock used.
             * @param pName - key associated with JNIEnv. Usually it's thread-name.
             * @return - JNIEnv or null.
             * @throws - no exceptions.
             */
            virtual JNIEnv * getJNIEnv( const bt_String& pName ) = 0;

            /**
             * Returns jobject, or null.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - associated key ( example: 'my_thread asset' ).
             * @throws - no exceptions.
             */
            virtual jobject * getObject( const bt_String& pName ) = 0;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * Add JNIEnv to cache.
             *
             * (?) All JNIEnvs deleted in #clear() method.
             *
             * @thread_safety - thread-lock used.
             * @param pName - associated key (thread name).
             * @param jniEnv - JNIEnv.
             * @throws - no exceptions.
             */
            virtual void addJNIEnv( const bt_String& pName, JNIEnv *const jniEnv ) = 0;

            /**
             * Removes JNIEnv from cache.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - Associated thread-name.
             * @throws - no exceptions.
             */
            virtual void removeJNIEnv( const bt_String& pName ) = 0;

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
             * @throws - no exceptions.
             */
            virtual void addObject( const bt_String& pName, jobject & pObject, JNIEnv *const jniEnv ) = 0;

            /**
             * Remove jobject from cache.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param pName - associated key ( example: 'my_thread asset' ).
             * @param jniEnv - JNIEnv used to create new 'Global Reference' for jobject.
             * @throws - no exceptions.
             */
            virtual void removeObject( const bt_String& pName, JNIEnv *const jniEnv ) = 0;

            /**
             * Clear JNICache.
             * Removes all jobjects, AAssetManager, JNIEnvs, etc.
             *
             * @thread_safety - thread-lock (synchronization) used.
             * @param jniEnv - JNIEnv used to delete 'Global Reference'.
             * If null, default used (first added).
             * @throws - no exceptions.
             */
            virtual void clear( JNIEnv * jniEnv ) = 0;

            // -----------------------------------------------------------

        }; /// bt::java::IJNICache

        // -----------------------------------------------------------

    } /// bt::java

} /// bt

using bt_IJNICache = bt::java::IJNICache;
#define BT_JAVA_I_JNI_CACHE_DECL

// -----------------------------------------------------------

#endif // !BT_JAVA_I_JNI_CACHE_HXX
