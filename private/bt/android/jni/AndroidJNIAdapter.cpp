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
#ifndef BT_ANDROID_JNI_ADAPTER_HPP
#include "../../../../public/bt/android/jni/AndroidJNIAdapter.hpp"
#endif // !BT_ANDROID_JNI_ADAPTER_HPP

// Include bt::java::JNIAdapter
#ifndef BT_JAVA_JNI_ADAPTER_HPP
#include "../../../../public/bt/java/jni/JNIAdapter.hpp"
#endif // !BT_JAVA_JNI_ADAPTER_HPP

// Include bt::android::AndroidJNICache
#ifndef BT_ANDROID_JNI_CACHE_HPP
#include "../../../../public/bt/android/jni/AndroidJNICache.hpp"
#endif // !BT_ANDROID_JNI_CACHE_HPP

// Include bt::java::JNICache
#ifndef BT_JAVA_JNI_CACHE_HPP
#include "../../../../public/bt/java/jni/JNICache.hpp"
#endif // !BT_JAVA_JNI_CACHE_HPP

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
// bt::android::AndroidJNIAdapter
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        AndroidJNIAdapter::AndroidJNIAdapter() = default;

        AndroidJNIAdapter::~AndroidJNIAdapter() = default;

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

// -----------------------------------------------------------
