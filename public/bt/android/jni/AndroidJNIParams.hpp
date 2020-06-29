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

#ifndef BT_ANDROID_JNI_PARAMS_HPP
#define BT_ANDROID_JNI_PARAMS_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::string
#ifndef BT_STRING_HPP
#include "../../cfg/bt_string.hpp"
#endif // !BT_STRING_HPP

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
         * AndroidJNIParams - Android JNI Params struct.
         * Used to transfer & store JNI-sepcific params, like globals limit, class names, etc.
         *
         * @version 0.1
        **/
        struct BT_API AndroidJNIParams final
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_STRUCT

            // ===========================================================
            // CONSTANTS & FIELDS
            // ===========================================================

            /** JNI Globals. **/
            unsigned char mGlobalsLimit;

            /** Kotlin/Java Class Name. **/
            bt_String mClassName;

            /** Method for Stop-Request. **/
            bt_String mStopMethod;

            /** Render Thread Name. **/
            bt_String mRenderThreadName;

            /**
             * @brief
             * AndroidJNIParams constructor.
             *
             * @throws - no exceptions.
            **/
            explicit AndroidJNIParams() BT_NOEXCEPT
                : mGlobalsLimit( 4 ),
                  mClassName( "com/company/android/game/jni/NativeUtil" ),
                  mStopMethod( "onStopRequest" ),
                  mRenderThreadName( "render_thread" )
            {
            }

            /**
             * @brief
             * AndroidJNIParams destructor.
             *
             * @throws - no exceptions.
            **/
            ~AndroidJNIParams() BT_NOEXCEPT = default;

            // -----------------------------------------------------------

        }; /// bt::android::AndroidJNIParams

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_AJNIParams = bt::android::AndroidJNIParams;
#define BT_ANDROID_JNI_PARAMS_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_JNI_PARAMS_HPP
