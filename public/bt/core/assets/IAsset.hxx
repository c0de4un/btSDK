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

#ifndef BT_CORE_I_ASSET_HXX
#define BT_CORE_I_ASSET_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

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
         * IAsset - Asset interface.
         *
         * @version 0.1
        **/
        class BT_API IAsset
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
             * IAsset destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~IAsset()
            {
            }

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns 'true' if loaded.
             *
             * @thread_safety - atomics used.
             * @throws - no exceptions.
            **/
            virtual bool isLoaded() const noexcept = 0;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Load this Asset.
             *
             * @thread_safety - thread-locks used.
             * @param pAsync - 'true' if Async-loading used, 'false' if current thread.
             * @param pThread - Thread-Type, used only for Async-mode.
             * @return - >= 0 if OK, < 0 if Error to Stop.
             * @throws - can throw exception (i/o, security, mutex).
            **/
            virtual unsigned char Load( const bool pAsync, const unsigned char pThread = 0 ) = 0;

            /**
             * @brief
             * Unload this Asset.
             *
             * @thread_safety - thread-locks used.
             * @param pAsync - 'true' if Async-loading used, 'false' if current thread.
             * @param pThread - Thread-Type, used only for Async-mode.
             * @throws - can throw exception.
            **/
            virtual void Unload( const bool pAsync, const unsigned char pThread ) = 0;

            // -----------------------------------------------------------

        }; /// bt::core::IAsset

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_IAsset = bt::core::IAsset;
#define BT_CORE_I_ASSET_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_I_ASSET_HXX
