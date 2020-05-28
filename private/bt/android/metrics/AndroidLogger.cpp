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
#ifndef BT_ANDROID_LOGGER_HPP
#include "../../../../public/bt/android/metrics/AndroidLogger.hpp"
#endif // !BT_ANDROID_LOGGER_HPP

// Include Android Log
#include <android/log.h>

// ===========================================================
// bt::android::AndroidLogger
// ===========================================================

namespace bt
{

    namespace android
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTOR & DESTRUCTOR
        // ===========================================================

        AndroidLogger::AndroidLogger( const char* const pTag ) BT_NOEXCEPT
            : mTag( pTag )
        {
        }

        AndroidLogger::~AndroidLogger() BT_NOEXCEPT
        {
        }

        // ===========================================================
        // bt::core::ILog
        // ===========================================================

        void AndroidLogger::Print( const char* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT
        {
            switch( logLvl )
            {
                case bt_ELogLevel::Info:
                    __android_log_print( ANDROID_LOG_INFO,  mTag, "%s", pMessage );
                    break;
                case bt_ELogLevel::Debug:
                default:
                    __android_log_print( ANDROID_LOG_DEBUG,  mTag, "%s", pMessage );
                    break;
                case bt_ELogLevel::Warning:
                    __android_log_print( ANDROID_LOG_WARN,  mTag, "%s", pMessage );
                    break;
                case bt_ELogLevel::Error:
                    __android_log_print( ANDROID_LOG_ERROR,  mTag, "%s", pMessage );
                    break;
            }
        }

        void AndroidLogger::Print_W( const wchar_t* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT
        {
        }

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

// -----------------------------------------------------------
