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

#ifndef BT_CORE_APPLICATION_HPP
#define BT_CORE_APPLICATION_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::System
#ifndef ECS_SYSTEM_HPP
#include "../../ecs/system/System.hpp"
#endif // !ECS_SYSTEM_HPP

// Include bt::core::AppParams
#ifndef BT_CORE_APP_PARAMS_HPP
#include "AppParams.hpp"
#endif // !BT_CORE_APP_PARAMS_HPP

// Include bt::events
#ifndef BT_CFG_EVENTS_HPP
#include "../../cfg/bt_events.hpp"
#endif // !BT_CFG_EVENTS_HPP

// Include bt::core::AsyncStorage
#ifndef BT_CORE_ASYNC_STORAGE_HPP
#include "../async/AsyncStorage.hpp"
#endif // !BT_CORE_ASYNC_STORAGE_HPP

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
         * Application - application-adapter class.
         * Allows to automatically handle app-level. Required due to
         * separation of Systems. For example, Graphics, Render and Game can be changed
         * dynamically at runtime using Application-Adapter API.
         *
         * @version 0.1
        **/
        BT_API class Application : public ecs_System
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

            /** Application instance. **/
            static bt_AsyncStorage<bt_sptr<Application>> mInstanceStorage;

            /** Params. **/
            bt_AppParams mParams;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Application constructor.
             *
             * @param appParams - Application Params.
             * @throws - can throw exception.
            **/
            explicit Application( const bt_AppParams& appParams );

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called on Termination of an instance.
             *
             * @thread_safety - instance thread-lock used.
             * @throws - no exceptions.
            **/
            virtual void onTerminate() BT_NOEXCEPT;

            // ===========================================================
            // DELETED
            // ===========================================================

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;
            Application(Application&&) = delete;
            Application& operator=(Application&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * Application destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~Application();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns Application instance.
             *
             * @thread_safety - atomics used.
             * @throws - no exceptions.
            **/
            static BT_API bt_sptr<Application> getInstance() noexcept;

            /**
             * @brief
             * Returns 'true' if Application instance is set.
             *
             * @thread_safety - thread-lock used.
             * @throws - no exceptions.
            **/
            static BT_API bool hasInstance() BT_NOEXCEPT;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize/Set Application instance.
             *
             * @thread_safety - main (system) thread-only.
             * @param pInstance - Application instance.
             * @throws - can throw exception.
            **/
            static BT_API void Initialize( bt_sptr<Application>& pInstance );

            /**
             * @brief
             * Terminate/Release Application instance.
             *
             * @thread_safety - atomics used.
             * @throws - can throw exception.
            **/
            static BT_API void Terminate();

            // ===========================================================
            // ISystem
            // ===========================================================

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

        }; /// bt::core::Application

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_App = bt::core::Application;
#define BT_CORE_APPLICATION_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_APPLICATION_HPP
