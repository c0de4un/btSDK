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

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// HEADER
#ifndef BT_CORE_COLOR_4F_HPP
#include "../../../../public/bt/core/math/Color4f.hpp"
#endif // !BT_CORE_COLOR_4F_HPP

// ===========================================================
// bt::core::Color4f
// ===========================================================

namespace bt
{

    namespace core
    {

        // -----------------------------------------------------------

        // ===========================================================
        // CONSTRUCTORS & DESTRUCTOR
        // ===========================================================

        Color4f::Color4f()
            : r(0),
            g(0),
            b(0),
            a(0)
        {
        }

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
        Color4f::Color4f( const bt_float_t pRed, const bt_float_t pGreen, const bt_float_t pBlue, const bt_float_t pAlpha) BT_NOEXCEPT
            : r(pRed),
            g(pGreen),
            b(pBlue),
            a(pAlpha)
        {
        }

        /**
         * @brief
         * Color4f destructor.
        **/
        Color4f::~Color4f() BT_NOEXCEPT = default;

        // ===========================================================
        // METHODS & OPERATORS
        // ===========================================================

        void Color4f::add( const Color4f& pOther ) BT_NOEXCEPT
        {
            r += pOther.r;
            g += pOther.g;
            b += pOther.b;
            a += pOther.a;
            this->norm();
        }

        void Color4f::sub( const Color4f& pOther ) BT_NOEXCEPT
        {
            r -= pOther.r;
            g -= pOther.g;
            b -= pOther.b;
            a -= pOther.a;
            this->norm();
        }

        void Color4f::div( const Color4f& pOther ) BT_NOEXCEPT
        {
            r /= pOther.r;
            g /= pOther.g;
            b /= pOther.b;
            a /= pOther.a;
            this->norm();
        }

        void Color4f::mul( const Color4f& pOther ) BT_NOEXCEPT
        {
            r *= pOther.r;
            g *= pOther.g;
            b *= pOther.b;
            a *= pOther.a;
            this->norm();
        }

        void Color4f::operator-( const Color4f& pOther ) BT_NOEXCEPT
        { this->sub(pOther); }

        void Color4f::operator*( const Color4f& pOther ) BT_NOEXCEPT
        { this->mul( pOther ); }

        void Color4f::operator/( const Color4f& pOther ) BT_NOEXCEPT
        { this->div(pOther); }

        void Color4f::operator+( const Color4f& pOther ) BT_NOEXCEPT
        { this->add(pOther); }

        void Color4f::norm() BT_NOEXCEPT
        {
            if ( r < 0 )
                r = 0;
            else if ( r > 1 )
                r = 1;

            if ( g < 0 )
                g = 0;
            else if ( g > 1 )
                g = 1;

            if ( b < 0 )
                b = 0;
            else if ( b > 1 )
                b = 1;

            if ( a < 0 )
                a = 0;
            else if ( a > 1 )
                a = 1;
        }

        // -----------------------------------------------------------

    } /// bt::core

} /// bt

// -----------------------------------------------------------
