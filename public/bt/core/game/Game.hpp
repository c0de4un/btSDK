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

#ifndef BT_CORE_GAME_HPP
#define BT_CORE_GAME_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::System
#ifndef ECS_SYSTEM_HPP
#include "../../ecs/system/System.hpp"
#endif // !ECS_SYSTEM_HPP

// Include bt::events
#ifndef BT_CFG_EVENTS_HPP
#include "../../cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

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
         * Game - base Game class.
         *
         * @version 0.1
        **/
        class BT_API Game : public ecs_System
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_CLASS

            // -----------------------------------------------------------

        protected:

            // -----------------------------------------------------------

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Game instance. **/
            static bt_AsyncStorage<bt_sptr<Game>> mInstanceHolder;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Game constructor.
             *
             * @throws - can throw exception:
             *           - mutex;
            **/
            explicit Game();

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called when Render Surface created/changed.
             *
             * @thread_safety - main Render-Thread.
             * @param pRestored - 'true' if surface restored/changed.
             * @throws - can throw exception.
            **/
            virtual bool onLoad( const bool pRestored );

            // ===========================================================
            // DELETED
            // ===========================================================

            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;
            Game(Game&&) = delete;
            Game& operator=(Game&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Game destructor.
             *
             * @throws - can throw exception:
             *           - mutex;
            **/
            virtual ~Game();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns Game instance.
             *
             * @thread_safety - atomics used.
             * @throws - no exceptions.
            **/
            static BT_API bt_sptr<Game> getInstance() noexcept;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize Game.
             *
             * @thread_safety - main thread only.
             * @param pInstance - Game instance.
             * @throws - can throw exception.
            **/
            static BT_API void Initialize( bt_sptr<Game>& pInstance );

            /**
             * @brief
             * Terminate Game.
             *
             * @thread_safety - main thread only.
             * @throws - can throw exception.
            **/
            static BT_API void Terminate();

            // ===========================================================
            // ecs::System
            // ===========================================================

            /**
             * @brief
             * Called on Event.
             *
             * @thread_safety - depends on implementation.
             * @param pEvent - Event to handle.
             * @param pAsync - 'true' if called in Async-mode.
             * @param pThread - Thread-Type.
             * @return - 0 to continue, 1 if handled to stop, -1 if error.
             * @throws - can throw exception. Exceptions collected & reported.
            **/
            virtual char OnEvent( ecs_sptr<ecs_IEvent> pEvent, const bool pAsync, const unsigned char pThread ) override;

            /**
             * @brief
             * Called on Event Error.
             *
             * @thread_safety - depends on implementation.
             * @param pEvent - Event to handle.
             * @param pException - Exception.
             * @param pAsync - 'true' if called in Async-mode.
             * @param pThread - Thread-Type.
             * @return - 0 to continue, 1 if handled to stop, -1 if error.
             * @throws - can throw exception. Exceptions collected & reported.
            **/
            virtual void onEventError( ecs_sptr<ecs_IEvent> pEvent, const std::exception& pException, const bool pAsync, const unsigned char pThread ) override;

            /**
             * @brief
             * Called when System starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() override;

            /**
             * @brief
             * Called whe System resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() override;

            /**
             * @brief
             * Called whe System pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() override;

            /**
             * @brief
             * Called whe System stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() override;

            // -----------------------------------------------------------

        }; /// bt::core::Game

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_Game = bt::core::Game;

#define BT_CORE_GAME_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_GAME_HPP
