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

#ifndef BT_CORE_LOAD_EVENT_HPP
#define BT_CORE_LOAD_EVENT_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::Event
#ifndef ECS_EVENT_HPP
#include "../../ecs/event/Event.hpp"
#endif // !ECS_EVENT_HPP

// Include bt::vector
#ifndef BT_CFG_VECTOR_HPP
#include "../../cfg/bt_vector.hpp"
#endif // !BT_CFG_VECTOR_HPP

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
         * LoadEvent - allows to notify Assets & their users,
         * that they can be loaded/restored.
         *
         * @version 0.1
        **/
        class BT_API LoadEvent final : public ecs_Event
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

            /** Flags. **/
            bt_vector<bool> mFlags;

            // ===========================================================
            // DELETED
            // ===========================================================

            LoadEvent(const LoadEvent&) = delete;
            LoadEvent& operator=(const LoadEvent&) = delete;
            LoadEvent(LoadEvent&&) = delete;
            LoadEvent& operator=(LoadEvent&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // CONSTANTS
            // ===========================================================

            /** Flags num. **/
            static constexpr const unsigned char ASSETS_FLAGS = 2;

            /** GPU-Related Assets flag. **/
            static constexpr const unsigned char GPU_ASSETS_FLAG = 0;

            /** Audio-Related Assets flag. **/
            static constexpr const unsigned char AUDIO_ASSETS_FLAG = 1;

            /** Reloading flag. Used to detect, that surface restored (lost of context, GC, device orientation change, etc). **/
            const bool mReload;

            // ===========================================================
            // CONSTRUCTOR & DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * LoadEvent constructor.
             *
             * @param pReloading - reloading (restore) flag. 'true', if Rendering Surface restored.
             * @param pCaller - Event Invoker. Can be null.
             * @throws - can throw exception.
            **/
            explicit LoadEvent( const bool pReloading, ecs_wptr<ecs_IEventInvoker> pCaller = ecs_sptr<ecs_IEventInvoker>( nullptr ) );

            /**
             * @brief
             * LoadEvent destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~LoadEvent();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Sets flag.
             *
             * @thread_safety - not required. Set only before sending.
             * @param flagName - Flag Index.
             * @param flagValue - Flag value.
             * @throws - no exceptions.
            **/
            void setFlag( const unsigned char flagName, const bool flagValue ) noexcept;

            /**
             * @brief
             * Returns 'true' if this events called for GPU-related users (textures, shaders, etc).
             *
             * @thread_safety - not required.
             * @throws - no exceptions.
            **/
            bool isGPU() const noexcept;

            /**
             * @brief
             * Returns 'true' if called for Audio-assets.
             *
             * @thread_safety - not required.
             * @throws - no exceptions.
            **/
            bool isAudio() const noexcept;

            // -----------------------------------------------------------

        }; /// bt::core::LoadEvent

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_LoadEvent = bt::core::LoadEvent;

// -----------------------------------------------------------

#endif // !BT_CORE_LOAD_EVENT_HPP