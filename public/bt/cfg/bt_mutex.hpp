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

#ifndef BT_CFG_MUTEX_HPP
#define BT_CFG_MUTEX_HPP

// -----------------------------------------------------------

// ===========================================================
// INCLUDES
// ===========================================================

// Include bt::platform
#ifndef BT_CFG_PLATFORM_HPP
#include "bt_platform.hpp"
#endif // !BT_CFG_PLATFORM_HPP

// PLATFORM
#if defined(ANDROID) || defined( BT_ANDROID ) // ANDROID

// Include bt::Android::AndroidMutex
#ifndef BT_ANDROID_MUTEX_HPP
#include "../android/async/AndroidMutex.hpp"
#endif // !BT_ANDROID_MUTEX_HPP

#elif defined( BT_WINDOWS ) // WINDOWS
#error "bt_mutex.hpp - Windows implementation required."
#elif defined( BT_LINUX ) // LINUX
#error "bt_mutex.hpp - Linux implementation required."
#else
#error "bt_mutex.hpp - platform configuration required."
#endif // ANDROID
// PLATFORM

// Include bt::core::SpinLock
#ifndef BT_CORE_SPIN_LOCK_HPP
#include "../core/async/SpinLock.hpp"
#endif // !BT_CORE_SPIN_LOCK_HPP

// ===========================================================
// CONFIGS
// ===========================================================

// -----------------------------------------------------------

#endif // !BT_CFG_MUTEX_HPP
