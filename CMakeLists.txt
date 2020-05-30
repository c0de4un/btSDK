# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine
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
set ( PROJECT_NAME "btEngine" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "btEngine project" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# OPTIONS & CONFIGS
# =================================================================================

# Platform
include ( "cmake/platform.cmake" )

# Options
include ( "cmake/bt_options.cmake" )

# Dependencies
include ("cmake/dependencies.cmake")

# =================================================================================
# HEADERS
# =================================================================================

set ( BT_HEADERS "${BT_PUBLIC_DIR}bt/bt.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BT_SOURCES "${BT_PRIVATE_DIR}bt/bt.cpp" )

# =================================================================================
# MODULES
# =================================================================================

# CORE
add_subdirectory ( "${BT_PUBLIC_DIR}bt/core" )

# ECS
add_subdirectory ( "${BT_PUBLIC_DIR}/bt/ecs" )

# OpenGL
if ( BT_OPEN_GL )
    add_subdirectory ( "${BT_PUBLIC_DIR}bt/gl" )
endif ( BT_OPEN_GL )

# Android
if ( ANDROID OR BT_ANDROID )
    add_subdirectory ( "${BT_PUBLIC_DIR}/bt/android" )
endif ( ANDROID OR BT_ANDROID )

# =================================================================================
# BUILD
# =================================================================================

# DEBUG
if ( BT_CMAKE_DEBUG )
    message ( STATUS "${PROJECT_NAME} - HEADERS: ${BT_HEADERS} ; SOURCES: ${BT_SOURCES}" )
endif ( BT_CMAKE_DEBUG )

# Build STATIC Library
if ( BT_BUILD_STATIC )

    # Create STATIC Library Object
    add_library ( btEngine STATIC ${BT_HEADERS} ${BT_SOURCES} )

endif ( BT_BUILD_STATIC )

# Build SHARED Library
if ( BT_BUILD_SHARED )
    # Create SHARED Library Object
    add_library ( btEngine SHARED ${BT_SOURCES} )

    # Configure Executable-Object
    set_target_properties ( btEngine PROPERTIES
            OUTPUT_NAME "shared_library_example"
            RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}" )
endif ( BT_BUILD_SHARED )

# Include & Link
if ( BT_BUILD_STATIC OR BT_BUILD_SHARED )
    # ECS
    include_directories ( "ecs" )

    # CORE
    include_directories("core")

    # ANDROID
    if ( ANDROID OR BT_ANDROID )
        include_directories("android")
    endif ( ANDROID OR BT_ANDROID )

    target_link_libraries ( btEngine btEngine_Core btEngine_ECS )

    # ANDROID
    if ( ANDROID OR BT_ANDROID )
        target_link_libraries ( btEngine btEngine_Android )
    endif ( ANDROID OR BT_ANDROID )

endif ( BT_BUILD_STATIC OR BT_BUILD_SHARED )

# INFO
message ( STATUS "${PROJECT_NAME} - ready" )