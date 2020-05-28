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
#ifndef BT_CORE_LOG_HPP
#include "../../../../public/bt/core/metrics/Log.hpp"
#endif // !BT_CORE_LOG_HPP

// Include bt::core::ILogger
#ifndef BT_CORE_I_LOGGER_HXX
#include "../../../../public/bt/core/metrics/ILogger.hxx"
#endif // !BT_CORE_I_LOGGER_HXX

// ===========================================================
// bt::core::Log
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // FIELDS
        // ===========================================================

        bt_ILogger* Log::mLogger(nullptr);

        // ===========================================================
        // CONSTRUCTOR && DESTRUCTOR
        // ===========================================================

        Log::Log() BT_NOEXCEPT
        {
        }

        Log::~Log() BT_NOEXCEPT
        {
        }

        // ===========================================================
        // GETTERS & SETTERS
        // ===========================================================

        bool Log::isInitialized() BT_NOEXCEPT
        { return mLogger != nullptr; }

        // ===========================================================
        // METHODS
        // ===========================================================

        void Log::Initialize( bt_ILogger* const pLogger ) BT_NOEXCEPT
        {
            if ( mLogger )
                return;

            mLogger = pLogger;
        }

        void Log::Print( const char* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT
        {
            if ( mLogger )
                mLogger->Print( pMessage, logLvl );
        }

        void Log::Print_W( const wchar_t* const pMessage, const unsigned char logLvl ) BT_NOEXCEPT
        {
            if ( mLogger )
                mLogger->Print_W( pMessage, logLvl );
        }

        void Log::Terminate() BT_NOEXCEPT
        {
            delete mLogger;
            mLogger = nullptr;
        }

        // -----------------------------------------------------------

    }

}

// -----------------------------------------------------------