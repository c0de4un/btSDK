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

#ifndef BT_CORE_ARCADE_ENGINE_HPP
#define BT_CORE_ARCADE_ENGINE_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::core::Engine
#ifndef BT_CORE_ENGINE_HPP
#include "Engine.hpp"
#endif // !BT_CORE_ENGINE_HPP

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
         * ArcadeEngine - simple engine implementation designed for robust games.
         *
         * @version 0.1
        **/
        class BT_API ArcadeEngine final : public bt_Engine
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
            // DELETED
            // ===========================================================

            ArcadeEngine(const ArcadeEngine&) = delete;
            ArcadeEngine& operator=(const ArcadeEngine&) = delete;
            ArcadeEngine(ArcadeEngine&&) = delete;
            ArcadeEngine& operator=(ArcadeEngine&&) = delete;

            // -----------------------------------------------------------

        protected:

            // -----------------------------------------------------------

            // ===========================================================
            // bt::core::Engine
            // ===========================================================

            /**
             * @brief
             * Called to load Assets.
             *
             * @thread_safety - render-thread only.
             * @param pReloading - 'true' if Assets should be reloaded.
             * @return 'true' if loaded, 'false' if failed to Stop App.
             * @throws - can throw exception.
            **/
            virtual bool onLoadAssets( const bool pReloading ) final;

            /**
             * @brief
             * Called to Draw.
             *
             * @thread_safety - render-thread only.
             * @throws - can throw exception.
            **/
            virtual void onDraw() final;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * ArcadeEngine constructor.
             *
             * @throws - can throw exception.
            **/
            explicit ArcadeEngine();

            /**
             * @brief
             * ArcadeEngine destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~ArcadeEngine();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            // ===========================================================
            // METHODS
            // ===========================================================

            // ===========================================================
            // bt::core::Engine
            // ===========================================================

            /**
             * @brief
             * Called when System starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() final;

            /**
             * @brief
             * Called whe System resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() final;

            /**
             * @brief
             * Called whe System pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() final;

            /**
             * @brief
             * Called whe System stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() final;

            // -----------------------------------------------------------

        }; /// bt::core::ArcadeEngine

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_ArcadeEngine = bt::core::ArcadeEngine;
#define BT_CORE_ARCADE_ENGINE_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_ARCADE_ENGINE_HPP
