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
#ifndef BT_ANDROID_JNI_CACHE_HPP
#include "../../../../public/bt/android/jni/AndroidJNICache.hpp"
#endif // !BT_ANDROID_JNI_CACHE_HPP

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
// bt::android::AndroidJNICache
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        AndroidJNICache::AndroidJNICache( const bt_AJNIParams& jniParams )
            : mAAssetManager( nullptr ),
              mAssetsManagerMutex(),
              mJNIEnvs(),
              mEnvMutex(),
              mObjects(),
              mObjectsMutex(),
              mParams( jniParams )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidJNICache created", bt_ELogLevel::Info );
#endif // DEBUG
        }

        AndroidJNICache::~AndroidJNICache()
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
            bt_Log::Print( u8"AndroidJNICache destroyed", bt_ELogLevel::Info );
#endif // DEBUG
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        void AndroidJNICache::setAAssetManager( jobject jAssetManager, JNIEnv *const jniEnv )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( jniEnv != nullptr && "AndroidJNICache::setAAssetManager - JNIEnv is null." );
#endif // DEBUG
                bt_SpinLock lock( &mAssetsManagerMutex );

                // Cache AAssetManager jobject
                addObject( "asset_manager", jAssetManager, jniEnv );

                // Get Native AAssetManager from jobject
                mAAssetManager = AAssetManager_fromJava( jniEnv, jAssetManager );

#if defined( BT_DEBUG ) || defined( DEBUG )
                // Check AAssetManager
                bt_assert( mAAssetManager != nullptr && "JNICache::setAAssetManager - failed to get AAssetManager from jobject ! Is jobject empty ?" );
#endif // DEBUG
        }

        AAssetManager * AndroidJNICache::getAAssetManager( ) const
        {
                bt_SpinLock lock( &mAssetsManagerMutex );
                return mAAssetManager;
        }

        // ===========================================================
        // IJNICache
        // ===========================================================

        JNIEnv * AndroidJNICache::getJNIEnv( const bt_String& pName )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::getJNIEnv - Thread-Name not set." );
#endif // DEBUG

                bt_SpinLock lock( &mEnvMutex );
                return mJNIEnvs[pName];
        }

        jobject * AndroidJNICache::getObject( const bt_String& pName )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::getObject - Key not set." );
#endif // DEBUG

                bt_SpinLock lock( &mObjectsMutex );

                // Search jobject
                auto position_ = mObjects.find( pName );

                // Return jobject
                if ( position_ != mObjects.cend( ) )
                        return( &position_->second );

                // Return null
                return nullptr;
        }

        void AndroidJNICache::addJNIEnv( const bt_String& pName, JNIEnv *const jniEnv )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::addJNIEnv - Key not set." );
                bt_assert( jniEnv != nullptr && "AndroidJNICache::addJNIEnv - JNIEnv is null." );
#endif // DEBUG

                bt_SpinLock lock( &mEnvMutex );
                mJNIEnvs[pName] = jniEnv;
        }

        void AndroidJNICache::removeJNIEnv( const bt_String& pName )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::removeJNIEnv - Key not set." );
#endif // DEBUG

                bt_SpinLock lock( &mEnvMutex );

                mJNIEnvs.erase( pName );
        }

        void AndroidJNICache::addObject( const bt_String& pName, jobject & pObject, JNIEnv *const jniEnv )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::addObject - Key not set." );
                bt_assert( jniEnv != nullptr && "AndroidJNICache::addObject - JNIEnv is null." );
#endif // DEBUG

                bt_SpinLock lock( &mObjectsMutex );

                // Create 'Global Reference'
                if ( jniEnv != nullptr )
                        jniEnv->NewGlobalRef( pObject );

                // Add jobject to the cache
                mObjects[pName] = pObject;
        }

        void AndroidJNICache::removeObject( const bt_String& pName, JNIEnv *const jniEnv )
        {
#if defined( BT_DEBUG ) || defined( DEBUG ) // DEBUG
                bt_assert( !pName.empty() && "AndroidJNICache::addObject - Key not set." );
                bt_assert( jniEnv != nullptr && "AndroidJNICache::addObject - JNIEnv is null." );
#endif // DEBUG

                bt_SpinLock lock( &mObjectsMutex );

                // Search
                auto jobjectPos_ = mObjects.find( pName );

                // Cancel, if not found
                if ( jobjectPos_ == mObjects.cend( ) )
                        return;

                // jobject
                jobject jobject_lr = jobjectPos_->second;

                // Delete 'Global Reference'
                if ( jniEnv != nullptr )
                        jniEnv->DeleteGlobalRef( jobject_lr );

                // Remove jobject from cache
                mObjects.erase( jobjectPos_ );
        }

        void AndroidJNICache::clear( JNIEnv * jniEnv )
        {
                // Get any JNIEnv
                if ( jniEnv == nullptr )
                        jniEnv = mJNIEnvs.begin( )->second;

#ifdef DEBUG // DEBUG
                // DEBUG-message
                bt_Log::Print( u8"JNICache::clear", bt_ELogLevel::Info );

                // Check JNIEnv
                bt_assert( jniEnv != nullptr && "JNICache::clear - JNIEnv is null !" );
#endif // DEBUG

                // Release AAssetManager
                if ( mAAssetManager != nullptr )
                {

                        // Remove jobject
                        //removeObject( "asset_manager", jniEnv );

                        // Reset pointer-value
                        mAAssetManager = nullptr;

                }

                // Delete 'Global Reference's
                if ( !mObjects.empty( ) )
                {

                        // jobjects map iterator
                        auto jobjectsIter_ = mObjects.begin( );

                        // jobjects map end-iterator
                        auto jobjectsEndIter_ = mObjects.cend( );

                        // Delete 'Global References'
                        while( jobjectsIter_ != jobjectsEndIter_ )
                        {

                                // Delete 'Global Reference'
                                //jniEnv->DeleteGlobalRef( jobjectsIter_->second );

                                // Next jobject
                                jobjectsIter_++;

                        }

                        // Remove jobjects
                        mObjects.clear( );
                }

                // Clear JNIEnv map
                mJNIEnvs.clear( );
        }

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

// -----------------------------------------------------------
