# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.ECS
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
set ( PROJECT_NAME "btEngine.ECS" )

# Project Version
set ( PROJECT_VERSION 0.0.1 )

# Project Description
set ( PROJECT_DESCRIPTION "btEngine ECS Module" )

# Configure Project
project ( PROJECT_NAME VERSION ${PROJECT_VERSION} DESCRIPTION PROJECT_DESCRIPTION LANGUAGES C CXX )

# =================================================================================
# HEADERS
# =================================================================================

set ( BT_ECS_HEADERS
        # CONFIG
        "ecs.hpp"
        "types/ecs_ids.hpp"
        "types/ecs_api.hpp"
        "types/ecs_assert.hpp"
        "types/ecs_log.hpp"
        "types/ecs_atomic.hpp"
        "types/ecs_numeric.hpp"
        "types/ecs_mutex.hpp"
        "types/ecs_memory.hpp"
        "types/ecs_vector.hpp"
        "types/ecs_map.hpp"
        "types/ecs_queue.hpp"
        "types/ecs_string.hpp"
        # ENTITY
        "entity/IEntity.hxx"
        "entity/Entity.hpp"
        "entity/EntitiesManager.hpp"
        # COMPONENT
        "component/Component.hpp"
        "component/ComponentsManager.hpp"
        # SYSTEM
        "system/ISystem.hxx"
        "system/System.hpp"
        "system/SystemsManager"
        # EVENT
        "event/IEvent.hxx"
        "event/IEventListener.hxx"
        "event/Event.hpp"
        "event/EventsManager.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

set ( BT_ECS_SOURCES
        "../../../private/bt/ecs/ecs.cpp"
        # ENTITY
        "../../../private/bt/ecs/entity/Entity.cpp"
        "../../../private/bt/ecs/entity/EntitiesManager.cpp"
        # COMPONENT
        "../../../private/bt/ecs/component/Component.cpp"
        "../../../private/bt/ecs/component/ComponentsManager.cpp"
        # SYSTEM
        "../../../private/bt/ecs/system/System.cpp"
        "../../../private/bt/ecs/system/SystemsManager.cpp"
        # EVENT
        "../../../private/bt/ecs/event/Event.cpp"
        "../../../private/bt/ecs/event/EventsManager.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Build STATIC Library
if ( BT_BUILD_STATIC )

    # Create STATIC Library Object
    add_library ( btEngine_ECS ${BT_ECS_HEADERS} ${BT_ECS_SOURCES} )

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
    add_library ( btEngine_ECS SHARED ${BT_ECS_SOURCES} )

    # Configure SHARED Library Object
    set_target_properties ( btEngine_ECS PROPERTIES
            PUBLIC_HEADER ${BT_ECS_HEADERS}
            RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
            VERSION ${PROJECT_VERSION} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - SHARED Library added." )
    endif ( BT_CMAKE_DEBUG )

endif ( BT_BUILD_SHARED )

# Link
if ( BT_BUILD_STATIC OR BT_BUILD_SHARED )

    # Include & Link btEngine.Core
    include_directories ( "../core" )
    target_link_libraries ( btEngine_ECS btEngine_Core )

    # Android
    if ( ANDROID )
        include_directories ( "../android" )
        target_link_libraries ( btEngine_ECS btEngine_Android )
    endif ( ANDROID )

endif ( BT_BUILD_STATIC OR BT_BUILD_SHARED )

# =================================================================================
# EXPORT
# =================================================================================

# Export Headers & Sources
if ( BT_EXPORT_SOURCES )
    set ( BT_HEADERS_EXPORT ${BT_HEADERS_EXPORT} ${BT_ECS_HEADERS} )
    set ( BT_SOURCES_EXPORT ${BT_SOURCES_EXPORT} ${BT_ECS_SOURCES} )

    # INFO
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - Sources exported" )
    endif ( BT_CMAKE_DEBUG )
endif ( BT_EXPORT_SOURCES )