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

#ifndef BT_CORE_RENDER_MANAGER_HPP
#define BT_CORE_RENDER_MANAGER_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include ecs::System
#ifndef ECS_SYSTEM_HPP
#include "../../ecs/system/System.hpp"
#endif // !ECS_SYSTEM_HPP

// Include bt::core::IGraphicsListener
#ifndef BT_CORE_I_GRAPHICS_LISTENER_HXX
#include "../graphics/IGraphicsListener.hxx"
#endif // !BT_CORE_I_GRAPHICS_LISTENER_HXX

// Include bt::memory
#ifndef BT_CFG_MEMORY_HPP
#include "../../cfg/bt_memory.hpp"
#endif // !BT_CFG_MEMORY_HPP

// Include bt::core::Color4f
#ifndef BT_CORE_COLOR_4F_HPP
#include "../math/Color4f.hpp"
#endif // !BT_CORE_COLOR_4F_HPP

// ===========================================================
// TYPES
// ===========================================================

namespace bt
{

    namespace core
    {

        /**
         * @brief
         * RenderManager - base renderer class.
         *
         * @version 0.1
        **/
        class BT_API RenderManager : public ecs_System, public bt_IGraphicsListener
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

            /** Engine instance. **/
            static bt_sptr<RenderManager> mInstance;

            /** Background Color .**/
            bt_Color4f mClearColor;

            // ===========================================================
            // CONSTRUCTOR
            // ===========================================================

            /**
             * @brief
             * RenderManager constructor.
             *
             * @throws - no exceptions.
            **/
            explicit RenderManager() BT_NOEXCEPT;

            // ===========================================================
            // DELETED
            // ===========================================================

            RenderManager(const RenderManager&) = delete;
            RenderManager& operator=(const RenderManager&) = delete;
            RenderManager(RenderManager&&) = delete;
            RenderManager& operator=(RenderManager&&) = delete;

            // -----------------------------------------------------------

        public:

            // -----------------------------------------------------------

            // ===========================================================
            // DESTRUCTOR
            // ===========================================================

            /**
             * @brief
             * RenderManager destructor.
             *
             * @throws - no exceptions.
            **/
            virtual ~RenderManager() BT_NOEXCEPT;

            // ===========================================================
            // GETTERS & SETTERS
            // ===========================================================

            /**
             * @brief
             * Returns Engine instance, or null.
             *
             * @thread_safety - not thread-safe.
             * @throws - no exceptions.
            **/
            static bt_sptr<RenderManager> getInstance() BT_NOEXCEPT;

            /**
             * @brief
             * Set Surface clear-color.
             *
             * @thread_safety - render thread-only.
             * @param pColor - color. Value copied/moved.
             * @throws - no exceptions.
            **/
            virtual void setSurfaceColor( const Color4f& pColor ) BT_NOEXCEPT;

            /**
             * @brief
             * Returns surface clear-color.
             *
             * @thread_safety - render-thread only.
             * @throws - no exceptions.
            **/
            Color4f getSurfaceColor() const BT_NOEXCEPT;

            // ===========================================================
            // ecs::System
            // ===========================================================

            /**
             * @brief
             * Called when RenderManager starting.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onStart() override;

            /**
             * @brief
             * Called whe RenderManager resuming from pause.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual bool onResume() override;

            /**
             * @brief
             * Called whe RenderManager pausing.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onPause() override;

            /**
             * @brief
             * Called whe RenderManager stopping.
             *
             * @thread_safety - thread-lock used.
             * @throws - can throw exception.
            **/
            virtual void onStop() override;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Initialize Render Manager.
             *
             * @thread_safety - main thread only.
             * @param pInstance - isntance to use.
             * @throws - can throw exceptions
            **/
            static void Initialize( bt_sptr<RenderManager> pInstance );

            /**
             * @brief
             * Terminate Render Manager.
             *
             * @thread_safety - main thread only.
             * @throws - can throw exception.
            **/
            static void Terminate();

            // -----------------------------------------------------------

        }; /// bt::core::RenderManager

    } /// bt::core

} /// bt

using bt_RenderManager = bt::core::RenderManager;
#define BT_CORE_RENDER_MANAGER_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_RENDER_MANAGER_HPP
