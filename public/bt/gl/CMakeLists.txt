# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.OpenGL (& ES)
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
set ( PROJECT_NAME "btEngine.GL" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "btEngine OpenGL (& ES) Module" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# HEADERS
# =================================================================================

set ( BT_GL_HEADERS
        # CONFIG
        "../cfg/bt_open_gl.hpp"
        # ASSETS
        # RENDER
        "render/IGLSurfaceListener.hxx"
        "render/events/GLSurfaceDrawEvent.hpp"
        "render/events/GLSurfaceReadyEvent.hpp"
        "render/GLRendererManager.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BT_GL_SOURCES
        # ASSETS
        # RENDER
        "../../../private/bt/gl/render/events/GLSurfaceDrawEvent.cpp"
        "../../../private/bt/gl/render/events/GLSurfaceReadyEvent.cpp"
        "../../../private/bt/gl/render/GLRenderManager.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Build STATIC Library
if ( BT_BUILD_STATIC )

    # Create STATIC Library Object
    add_library ( btEngine_GL ${BT_GL_HEADERS} ${BT_GL_SOURCES} )

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
    add_library ( btEngine_GL SHARED ${BT_GL_SOURCES} )

    # Configure SHARED Library Object
    set_target_properties ( btEngine_GL PROPERTIES
            PUBLIC_HEADER ${BT_GL_HEADERS}
            RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
            VERSION ${PROJECT_VERSION} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - SHARED Library added." )
    endif ( BT_CMAKE_DEBUG )

endif ( BT_BUILD_SHARED )

# Link
if ( BT_BUILD_SHARED OR BT_BUILD_STATIC )

    # Include btEngine.Core
    include_directories ( "../cfg" )
    include_directories ( "../core" )

    # Include ECS
    include_directories ( "../ecs" )

    # Link btEngine
    target_link_libraries ( btEngine_GL btEngine_Core btEngine_ECS )

    if ( BT_OPEN_GL_ES ) # Mobile
        if ( ANDROID ) # Android
            target_link_libraries ( btEngine_GL ${OpenGL} )
        else ( ANDROID )
            message ( FATAL_ERROR "${PROJECT_NAME} - configuration required." )
        endif ( ANDROID )
    else ( BT_OPEN_GL_ES ) # Desktop
        message ( FATAL_ERROR "${PROJECT_NAME} - Desktop configuration required." )
    endif ( BT_OPEN_GL_ES )

endif ( BT_BUILD_SHARED OR BT_BUILD_STATIC )

# =================================================================================
# EXPORT
# =================================================================================

# Export Headers & Sources
if ( BT_EXPORT_SOURCES )
    set ( BT_HEADERS_EXPORT ${BT_HEADERS_EXPORT} ${BT_GL_HEADERS} )
    set ( BT_SOURCES_EXPORT ${BT_SOURCES_EXPORT} ${BT_GL_SOURCES} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - Sources exported" )
    endif ( BT_CMAKE_DEBUG )
endif ( BT_EXPORT_SOURCES )