/**
* Copyright © 2020 Denis Z. (code4un@yandex.ru) All rights reserved.
* Authors: Denis Z. (code4un@yandex.ru)
* All rights reserved.
* Language: C++
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
**/

#ifndef BT_CORE_GRAPHICS_MANAGER_HPP
#define BT_CORE_GRAPHICS_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::System
#ifndef ECS_SYSTEM_HPP
#include "../../ecs/system/System.hpp"
#endif // !ECS_SYSTEM_HPP

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "../../cfg/bt_api.hpp"
#endif // !BT_CFG_API_HPP

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

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
         * GraphicsSettings - graphics settings struct.
         * Designed to support extensions.
         *
         * @version 0.1
        **/
        struct BT_API GraphicsSettings
        {

            // -----------------------------------------------------------

            BT_STRUCT

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Window Width. **/
            int mWindowWidth;

            /** Window Height. **/
            int mWindowHeight;

            /** Surface Width. **/
            int mSurfaceWidth;

            /** Surface Height. **/
            int mSurfaceHeight;

            /** Color Depth. **/
            unsigned char mColorDepth;

            // -----------------------------------------------------------

        }; /// bt::core::GraphicsSettings

        // -----------------------------------------------------------

        /**
         * @brief
         * GraphicsManager - handles graphics (GDI, like Windows, Forms, Frames & Layouts).
         *
         * @version 0.1
        **/
        class BT_API GraphicsManager : public ecs_System
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

            /** GraphicsManager instance. **/
            static AsyncStorage<bt_sptr<GraphicsManager>> mInstanceStorage;

            /** Current Graphics Settings. **/
            GraphicsSettings mSettings;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * GraphicsManager constructor.
             *
             * @param pSettings - initial Graphics Settings, value copied.
             * @throws - can throw exception.
            **/
            explicit GraphicsManager( const GraphicsSettings& pSettings );

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called when GraphicsManager instance is being terminating.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onTerminate();

            // ===========================================================
            // DELETED
            // ===========================================================

            GraphicsManager(const GraphicsManager&) = delete;
            GraphicsManager& operator=(const GraphicsManager&) = delete;
            GraphicsManager(GraphicsManager&&) = delete;
            GraphicsManager& operator=(GraphicsManager&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * GraphicsManager destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~GraphicsManager();

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns current settings.
             *
             * @thread_safety - thread-safe.
             * @return - copy of the current graphics settings.
             * @throws - no exceptions.
            **/
            GraphicsSettings getSettings() const BT_NOEXCEPT;

            /**
             * @brief
             * Returns Graphics Manager instance, or null.
             *
             * @thread_safety - not thread-safe.
             * @throws - no exceptions.
            **/
            static bt_sptr<GraphicsManager> getInstance() BT_NOEXCEPT;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize GraphicsManager.
             *
             * @thread_safety - main thread only.
             * @param pInstance - isntance to use.
             * @throws - can throw exceptions
            **/
            static void Initialize( bt_sptr<GraphicsManager> pInstance );

            /**
             * @brief
             * Terminate Graphics Manager.
             *
             * @thread_safety - main thread only.
             * @throws - can throw exception.
            **/
            static void Terminate();

            // -----------------------------------------------------------

        }; /// bt::core::GraphicsManager

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_Graphics = bt::core::GraphicsManager;
using bt_GraphicsSettings = bt::core::GraphicsSettings;
#define BT_CORE_GRAPHICS_SETTINGS_DECL
#define BT_CORE_GRAPHICS_MANAGER_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_GRAPHICS_MANAGER_HPP
