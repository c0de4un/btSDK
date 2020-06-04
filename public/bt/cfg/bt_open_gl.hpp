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

#ifndef BT_CFG_OPEN_GL_HPP
#define BT_CFG_OPEN_GL_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::api
#ifndef BT_CFG_API_HPP
#include "bt_api.hpp"
#endif // !BT_CFG_API_HPP

// Default Defines
#ifndef BT_GL_MAJOR

#define BT_GL_MAJOR 3
#define BT_GL_MINOR 0

#warning "bt_open_gl.hpp - automatically setting open gl api version."

#endif
// Default Defines

// PLATFORM
#if defined( BT_WINDOWS ) || defined( BT_LINUX ) // DESKTOP

// Include GLEW
#ifndef _glew_h_
#define GLEW_STATIC
#include <glew.h>
#endif

// Include GLFW
#ifndef _glfw3_h_
#include <glfw3.h>
#endif

#elif defined( ANDROID ) || defined( BT_ANDROID ) // ES

#ifndef BT_OPEN_GL_ES
#define BT_OPEN_GL_ES 1
#warning "bt_open_gl.hpp - ES automatically detected."
#endif // !BT_OPEN_GL_ES

#if BT_GL_MAJOR == 2 // OpenGL 2.0

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#elif BT_GL_MAJOR == 3 // OpenGL 3+

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#else
#error "bt_open_gl.hpp - configuration required."
#endif

#else
#error "bt_open_gl.hpp - configuration required."
#endif
// PLATFORM

// ===========================================================
// CONFIGS
// ===========================================================

// -----------------------------------------------------------

#endif // !BT_CFG_OPEN_GL_HPP
