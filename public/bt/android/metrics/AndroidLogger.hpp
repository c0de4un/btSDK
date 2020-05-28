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

#ifndef BT_ANDROID_LOGGER_HPP
#define BT_ANDROID_LOGGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::ILogger
#ifndef BT_CORE_I_LOGGER_HXX
#include "../../core/metrics/ILogger.hxx"
#endif // !BT_CORE_I_LOGGER_HXX

// Include bt::core::Log
#ifndef BT_CORE_LOG_HPP
#include "../../../../public/bt/core/metrics/Log.hpp"
#endif // !BT_CORE_LOG_HPP

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
         * AndroidLogger - default logger for Android.
         *
         * @version 0.1
        **/
        class BT_API AndroidLogger final : public bt_ILogger
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
            // CONSTANTS
            // ===========================================================

            /** Tag **/
            const char* const mTag;

            // ===========================================================
            // FIELDS
            // ===========================================================

            // ===========================================================
            // DELETED
            // ===========================================================

            AndroidLogger(const AndroidLogger&) = delete;
            AndroidLogger& operator=(const AndroidLogger&) = delete;
            AndroidLogger(AndroidLogger&&) = delete;
            AndroidLogger& operator=(AndroidLogger&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * AndroidLogger constructor.
             *
             * @param pTag - Android Log-cat tag.
             * @throws - no exceptions.
            **/
            explicit AndroidLogger( const char* const pTag = "btEngine" ) BT_NOEXCEPT;

            /**
             * @brief
             * AndroidLogger destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~AndroidLogger() BT_NOEXCEPT;

            // ===========================================================
            // bt::core::ILog
            // ===========================================================

            /**
             * @brief
             * Print log-message.
             *
             * @thread_safety - depends on implementation.
             * @param pMessage - c-string (UTF-8 or ANSI), value copied.
             * @param logLvl - Log-Level (Info, Debug, Warning, Error).
             * @throws - no exceptions.
            **/
            virtual void Print( const char* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT final;

            /**
             * @brief
             * Print log-message in Unicode.
             *
             * @thread_safety - depends on implementation.
             * @param pMessage - wchar_t c-string (Unicode), value copied.
             * @param logLvl - Log-Level (Info, Debug, Warning, Error).
             * @throws - no exceptions.
            **/
            virtual void Print_W( const wchar_t* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT final;

            // -----------------------------------------------------------

        }; /// bt::core::AndroidLogger

        // -----------------------------------------------------------

    } /// bt::android

} /// bt

using bt_AndroidLogger = bt::android::AndroidLogger;
#define BT_ANDROID_LOGGER_DECL

// -----------------------------------------------------------

#endif // !BT_ANDROID_LOGGER_HPP
