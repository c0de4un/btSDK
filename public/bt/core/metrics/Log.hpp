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

#ifndef BT_CORE_LOG_HPP
#define BT_CORE_LOG_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

// Include bt::core::ILogger
#ifndef BT_CORE_I_LOGGER_HXX
#include "ILogger.hxx"
#endif // !BT_CORE_I_LOGGER_HXX

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * ELogLevel - logging levels enum.
         *
         * @version 0.1
        **/
        BT_ENUM_TYPE BT_API ELogLevel : unsigned char
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_ENUM

            // ===========================================================
            // CONSTANTS
            // ===========================================================

            Info = 0,
            Debug = 1,
            Warning = 2,
            Error = 3

            // -----------------------------------------------------------

        }; /// bt::core::ELogLeevel

        // -----------------------------------------------------------

        /**
         * @brief
         * Log - log class.
         *
         * @version 0.1
        **/
        class BT_API Log
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

            /** ILogger instance. **/
            static bt_ILogger* mLogger;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Log constructor.
             *
             * @throws - no exceptions.
            **/
            explicit Log() BT_NOEXCEPT;

            // ===========================================================
            // DELETED
            // ===========================================================

            Log(const Log&) = delete;
            Log& operator=(const Log&) = delete;
            Log(Log&&) = delete;
            Log& operator=(Log&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Log destructor.
             *
             * @throws - no exceptions.
            **/
            ~Log() BT_NOEXCEPT;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns 'true' if logger initialized.
             *
             * @thread_safety - not thread-safe.
             * @throws - no exceptions.
            **/
            static bool isInitialized() BT_NOEXCEPT;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize Log.
             *
             * @thread_safety - main thread only.
             * @param pLogger - ILogger instance to use.
             * @throws - no exceptions.
            **/
            static void Initialize( bt_ILogger* const pLogger ) BT_NOEXCEPT;

            /**
             * @brief
             * Print log-message.
             *
             * @thread_safety - depends on implementation.
             * @param pMessage - c-string (UTF-8 or ANSI), value copied.
             * @param logLvl - Log-Level (Info, Debug, Warning, Error).
             * @throws - no exceptions.
            **/
            static void Print( const char* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT;

            /**
             * @brief
             * Print log-message in Unicode.
             *
             * @thread_safety - depends on implementation.
             * @param pMessage - wchar_t c-string (Unicode), value copied.
             * @param logLvl - Log-Level (Info, Debug, Warning, Error).
             * @throws - no exceptions.
            **/
            static void Print_W( const wchar_t* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT;

            /**
             * @brief
             * Terminate (release) Log.
             *
             * @thread_safety - main thread only.
             * @throws - no exceptions.
            **/
            static void Terminate() BT_NOEXCEPT;

            // -----------------------------------------------------------

        }; /// bt::core::Log

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_Log = bt::core::Log;
using bt_ELogLevel = bt::core::ELogLevel;

// -----------------------------------------------------------

#endif // !BT_CORE_LOG_HPP
