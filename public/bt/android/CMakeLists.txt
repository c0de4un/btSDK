# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.Android
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# =================================================================================
# CMake Meta-Data
# =================================================================================

cmake_minimum_required(VERSION 3.5)

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( PROJECT_NAME "btEngine.Android" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "btEngine Android Module" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# OPTIONS & CONFIGS
# =================================================================================



# =================================================================================
# HEADERS
# =================================================================================

set ( BT_ANDROID_HEADERS
        # IO
        "io/AndroidFile.hpp"
        "io/AndroidInputStream.hpp"
        "io/AndroidOutputStream.hpp"
        # JNI
        "../java/jni/IJNIAdapter.hxx"
        "../java/jni/IJNICache.hxx"
        "../java/jni/JNICache.hpp"
        "../java/jni/JNIAdapter.hpp"
        "jni/AndroidJNIParams.hpp"
        "jni/AndroidJNIAdapter.hpp"
        "jni/AndroidJNICache.hpp"
        "jni/IAndroidNative.hxx"
        # ASYNC
        "async/AndroidMutex.hpp"
        # GRAPHICS
        "graphics/AndroidGraphics.hpp"
        # APPLICATION
        "app/AndroidApp.hpp"
        # METRICS
        "metrics/AndroidLogger.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BT_ANDROID_SOURCES
        # IO
        "../../../private/bt/android/io/AndroidFile.cpp"
        "../../../private/bt/android/io/AndroidInputStream.cpp"
        "../../../private/bt/android/io/AndroidOutputStream.cpp"
        # JNI
        "../../../private/bt/java/jni/JNIAdapter.cpp"
        "../../../private/bt/java/jni/JNICache.cpp"
        "../../../private/bt/android/jni/AndroidJNICache.cpp"
        "../../../private/bt/android/jni/AndroidJNIAdapter.cpp"
        # ASYNC
        "../../../private/bt/android/async/AndroidMutex.cpp"
        # GRAPHICS
        "../../../private/bt/android/graphics/AndroidGraphics.cpp"
        # APPLICATION
        "../../../private/bt/android/app/AndroidApp.cpp"
        # METRICS
        "../../../private/bt/android/metrics/AndroidLogger.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Build STATIC Library
if ( BT_BUILD_STATIC )

    # Create STATIC Library Object
    add_library ( btEngine_Android STATIC ${BT_ANDROID_HEADERS} ${BT_ANDROID_SOURCES} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - STATIC Library added." )
    endif ( BT_CMAKE_DEBUG )

endif ( BT_BUILD_STATIC )

# Build SHARED Library
if ( BT_BUILD_SHARED )

    if ( WIN32 OR WIN64 OR MINGW32 OR MINGW64 )
        # Export all Symbols by default (on Windows creates '.lib'+ '.dll').
        set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
    endif ( WIN32 OR WIN64 OR MINGW32 OR MINGW64 )

    # Create SHARED Library Object
    add_library ( btEngine_Android SHARED ${BT_ANDROID_SOURCES} )

    # Configure SHARED Library Object
    set_target_properties ( btEngine_Android PROPERTIES
            PUBLIC_HEADER ${BT_ANDROID_HEADERS}
            RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
            VERSION ${PROJECT_VERSION} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - SHARED Library added." )
    endif ( BT_CMAKE_DEBUG )

endif ( BT_BUILD_SHARED )

# Include & Link
if ( BT_BUILD_SHARED OR BT_BUILD_STATIC )
    # Include btEngine.Core
    include_directories ( "../cfg" )
    include_directories ( "../core" )

    # Include btEnigne.GL
    include_directories ( "../gl" )

    # Link
    target_link_libraries ( btEngine_Android btEngine_Core btEngine_GL ${log-lib} ${android_lib} )
endif ( BT_BUILD_SHARED OR BT_BUILD_STATIC )

# =================================================================================
# EXPORT
# =================================================================================

# Export Headers & Sources
if ( BT_EXPORT_SOURCES )
    set ( BT_HEADERS_EXPORT ${BT_HEADERS_EXPORT} ${BT_ANDROID_HEADERS} )
    set ( BT_SOURCES_EXPORT ${BT_SOURCES_EXPORT} ${BT_ANDROID_SOURCES} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - Sources exported" )
    endif ( BT_CMAKE_DEBUG )
endif ( BT_EXPORT_SOURCES )