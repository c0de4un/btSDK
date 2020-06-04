# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.Core
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
set ( PROJECT_NAME "btEngine.Core" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "btEngine Core Module" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# OPTIONS & CONFIGS
# =================================================================================

# =================================================================================
# IMPORT
# =================================================================================

# GLM
include_directories ( "${GLM_LIB_DIR}" )

# =================================================================================
# HEADERS
# =================================================================================

set ( BT_CORE_HEADERS
        # CONFIG
        "../cfg/bt_api.hpp"
        "../cfg/bt_assert.hpp"
        "../cfg/bt_platform.hpp"
        "../cfg/bt_atomic.hpp"
        "../cfg/bt_numeric.hpp"
        "../cfg/bt_mutex.hpp"
        "../cfg/bt_queue.hpp"
        "../cfg/bt_stream.hpp"
        "../cfg/bt_vector.hpp"
        "../cfg/bt_map.hpp"
        "../cfg/bt_log.hpp"
        "../cfg/bt_memory.hpp"
        "../cfg/bt_math.hpp"
        "../cfg/bt_bits.hpp"
        "../cfg/bt_sets.hpp"
        "../cfg/bt_systems.hpp"
        "../cfg/bt_events.hpp"
        "../cfg/bt_components.hpp"
        "../cfg/bt_entities.hpp"
        # CONTAINERS
        "containers/AsyncVector.hpp"
        "containers/AsyncArray.hpp"
        "containers/AsyncDeque.hpp"
        "containers/AsyncMap.hpp"
        "containers/IMapIterator.hxx"
        # ASYNC
        "async/IMutex.hxx"
        "async/Mutex.hpp"
        "async/ILock.hxx"
        "async/Lock.hpp"
        "async/SpinLock.hpp"
        # MATH
        "math/Color4f.hpp"
        # MEMORY
        "memory/IDMap.hpp"
        "memory/IDVector.hpp"
        # METRICS
        "metrics/ILogger.hxx"
        "metrics/Log.hpp"
        # GRAPHICS
        "graphics/IGraphicsListener.hxx"
        "graphics/GraphicsManager.hpp"
        # RENDER
        "render/RenderManager.hpp"
        # ENGINE
        "engine/ArcadeEngine.hpp"
        "engine/Engine.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BT_CORE_SOURCES
        # ASYNC
        "../../../private/bt/core/async/Mutex.cpp"
        "../../../private/bt/core/async/Lock.cpp"
        "../../../private/bt/core/async/SpinLock.cpp"
        # MATH
        "../../../private/bt/core/math/Color4f.cpp"
        # METRICS
        "../../../private/bt/core/metrics/Log.cpp"
        # GRAPHICS
        "../../../private/bt/core/graphics/GraphicsManager.cpp"
        # RENDER
        "../../../private/bt/core/render/RenderManager.cpp"
        # ENGINE
        "../../../private/bt/core/engine/ArcadeEngine.cpp"
        "../../../private/bt/core/engine/Engine.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Build STATIC Library
if ( BT_BUILD_STATIC )

    # Create STATIC Library Object
    add_library ( btEngine_Core STATIC ${BT_CORE_HEADERS} ${BT_CORE_SOURCES} )

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
    add_library ( btEngine_Core SHARED ${BT_CORE_SOURCES} )

    # Configure SHARED Library Object
    set_target_properties ( btEngine_Core PROPERTIES
            PUBLIC_HEADER ${BT_CORE_HEADERS}
            RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
            VERSION ${PROJECT_VERSION} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - SHARED Library added." )
    endif ( BT_CMAKE_DEBUG )

endif ( BT_BUILD_SHARED )

# Include & Link
if ( BT_BUILD_STATIC OR BT_BUILD_SHARED )

    # Include
    include_directories ( "../ecs" ) # ECS

    # Link
    target_link_libraries ( btEngine_Core btEngine_ECS )

endif ( BT_BUILD_STATIC OR BT_BUILD_SHARED )

# =================================================================================
# EXPORT
# =================================================================================

# Export Headers & Sources
if ( BT_EXPORT_SOURCES )
    set ( BT_HEADERS_EXPORT ${BT_HEADERS_EXPORT} ${BT_CORE_HEADERS} )
    set ( BT_SOURCES_EXPORT ${BT_SOURCES_EXPORT} ${BT_CORE_SOURCES} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - Sources exported" )
    endif ( BT_CMAKE_DEBUG )
endif ( BT_EXPORT_SOURCES )