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

#ifndef BT_CORE_I_DRAWABLE_HXX
#define BT_CORE_I_DRAWABLE_HXX

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::numeric
#ifndef BT_CFG_NUMERIC_HPP
#include "../../cfg/bt_numeric.hpp"
#endif // !BT_CFG_NUMERIC_HPP

// ===========================================================
// FORWARD-DECLARATIONS
// ===========================================================

// Forward-Declare RenderManager
#ifndef BT_CORE_RENDER_MANAGER_DECL
#define BT_CORE_RENDER_MANAGER_DECL
namespace bt { namespace core { class RenderManager; } }
using bt_RenderManager = bt::core::RenderManager;
#endif // !BT_CORE_RENDER_MANAGER_DECL

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
         * IDrawable - interface for drawable-objects.
         *
         * @version 0.1
        **/
        class BT_API IDrawable
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
             * IDrawable destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~IDrawable() = default;

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called by Renderer every frame draw.
             *
             * @thread_safety - render-thread only (one of them).
             * @param elapsedSeconds - time in seconds elapsed since previous frame.
             * 60 FPS is 0.016s. To get nano-seconds or milliseconds, use Render API.
             * @param renderManager - RenderManager instance.
             * @throws - can throw exception. Errors collected & reported.
            **/
            virtual void Draw( const bt_real_t elapsedSeconds, bt_RenderManager*const renderManager ) = 0;

            // -----------------------------------------------------------

        }; /// bt::core::IDrawable

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_IDrawable = bt::core::IDrawable;
#define BT_CORE_I_DRAWABLE_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_I_DRAWABLE_HXX
