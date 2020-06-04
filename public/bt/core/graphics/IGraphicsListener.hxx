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

#ifndef BT_CORE_I_GRAPHICS_LISTENER_HXX
#define BT_CORE_I_GRAPHICS_LISTENER_HXX

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

#ifndef BT_CORE_GRAPHICS_MANAGER_DECL
#define BT_CORE_GRAPHICS_MANAGER_DECL
namespace bt
{
    namespace core
    {
        struct GraphicsSettings;
        class GraphicsManager;
    }
}
using bt_Graphics = bt::core::GraphicsManager;
using bt_GraphicsSettings = bt::core::GraphicsSettings;
#endif // !BT_CORE_GRAPHICS_MANAGER_DECL

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
         * IGraphicsListener - interface to handle direct Graphics-Manager (System) callbacks.
         * Preferred before Events model due to speed.
         *
         * @version 0.1
        **/
        class BT_API IGraphicsListener
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
             * IGraphicsListener destructor.
             *
             * @throws - can throw exception.
            **/
            virtual ~IGraphicsListener()
            {
            }

            // ===========================================================
            // METHODS
            // ===========================================================

            /**
             * @brief
             * Called when Graphics prepared rendering surface.
             *
             * @thread_safety - render-thread only.
             * @return - 'true' if OK, 'false' to stop engine.
             * @throws - can throw exception.
            **/
            virtual bool onSurfaceReady() = 0;

            /**
             * @brief
             * Called on every frame Draw.
             *
             * @thread_safety - render-thread only.
             * @param elapsedTime - milliseconds, elapsed since previous draw-call.
             * @throws - can throw exception.
            **/
            virtual void onSurfaceDraw( const bt_real_t elapsedTime ) = 0;

            // -----------------------------------------------------------

        }; /// bt::core::IGraphicsListener

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_IGraphicsListener = bt::core::IGraphicsListener;
#define BT_CORE_I_GRAPHICS_LISTENER_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_I_GRAPHICS_LISTENER_HXX
