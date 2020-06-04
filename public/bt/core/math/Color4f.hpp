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

#ifndef BT_CORE_COLOR_4F_HPP
#define BT_CORE_COLOR_4F_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::numeric
#ifndef BT_CFG_NUMERIC_HPP
#include "../../cfg/bt_numeric.hpp"
#endif // !BT_CFG_NUMERIC_HPP

// ===========================================================
// bt::core::Color4f
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        /**
         * @brief
         * Color4f - 4 float (double || real) values color struct.
         *
         * @version 0.1
        **/
        struct BT_STRUCT Color4f
        {

            // -----------------------------------------------------------

            // ===========================================================
            // META
            // ===========================================================

            BT_CLASS

            // ===========================================================
            // FIELDS
            // ===========================================================

            /** Components. **/
            bt_float_t r, g, b, a;

            // ===========================================================
            // CONSTRUCTORS & DESTRUCTOR
            // ===========================================================

            explicit Color4f();

            /**
             * @brief
             * Color4f constructor.
             *
             * @param r - Red.
             * @param g - Green.
             * @param b - Blue.
             * @param a - Alpha.
             * @throws - no exceptions.
            **/
            explicit Color4f( const bt_float_t r, const bt_float_t g, const bt_float_t b, const bt_float_t a) BT_NOEXCEPT;

            /**
             * @brief
             * Color4f destructor.
            **/
            ~Color4f() BT_NOEXCEPT;

            // ===========================================================
            // DELETED
            // ===========================================================



            // ===========================================================
            // METHODS & OPERATORS
            // ===========================================================

            void add( const Color4f& pOther ) BT_NOEXCEPT;

            void sub( const Color4f& pOther ) BT_NOEXCEPT;

            void div( const Color4f& pOther ) BT_NOEXCEPT;

            void mul( const Color4f& pOther ) BT_NOEXCEPT;

            void operator-( const Color4f& pOther ) BT_NOEXCEPT;

            void operator*( const Color4f& pOther ) BT_NOEXCEPT;

            void operator/( const Color4f& pOther ) BT_NOEXCEPT;

            void operator+( const Color4f& pOther ) BT_NOEXCEPT;

            void norm() BT_NOEXCEPT;

            // -----------------------------------------------------------

        }; /// bt::core::Color4f

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

using bt_Color4f = bt::core::Color4f;
#define BT_CORE_COLOR_4F_DECL

// -----------------------------------------------------------

#endif // !BT_CORE_COLOR_4F_HPP
