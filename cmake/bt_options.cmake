# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.options
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - BUILD-TYPE - - - - - - - - - - - - - - - - - -

# Debug/Release Detection
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set ( DEBUG ON )
    set ( BT_DEBUG ON )
    add_definitions ( -DBT_DEBUG=1 )
    add_definitions ( -DDEBUG=1 )
    set ( BT_BUILD_TYPE_DIR "debug" )
else ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set ( DEBUG OFF )
    set ( BT_DEBUG OFF )
    set ( BT_BUILD_TYPE_DIR "release" )
endif ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

# - - - - - - - - - - - - - - - - - OPTIONS - - - - - - - - - - - - - - - - - -

set ( BT_PUBLIC_DIR "public/" )
set ( BT_PRIVATE_DIR "private/" )

option ( BT_CMAKE_DEBUG "Log-Output debug message about cmake-logic" ON )

option ( BT_BUILD_SDK "Build enabled SDK modules." ON )
option ( BT_TESTS "Unit testing" ON )
option ( BT_BUILD_STATIC "Build modules as STATIC libraries." ON )
option ( BT_BUILD_SHARED "Build modules as SHARED libraries." OFF )
option ( BT_EXPORT_SOURCES "Append all sources & headers to output-vars" OFF )

# - - - - - - - - - - - - - - - - - RENDER - - - - - - - - - - - - - - - - - -

# Render API
if ( BT_OPEN_GL ) # OpenGL (& ES) API
    if ( NOT BT_GL_VERSION_MAJOR OR NOT DEFINED BT_GL_VERSION_MINOR )
        message ( FATAL_ERROR "${PROJECT_NAME} - OpenGL version required, set <BT_GL_VERSION_MAJOR> & <BT_GL_VERSION_MINOR>." )
    endif ( NOT BT_GL_VERSION_MAJOR OR NOT DEFINED BT_GL_VERSION_MINOR )

    if ( BT_GL_VERSION_MAJOR EQUAL 2 )
        add_definitions ( -DBT_GL_MAJOR=2 )
    elseif ( BT_GL_VERSION_MAJOR EQUAL 3 )
        add_definitions ( -DBT_GL_MAJOR=3 )
    else ( BT_GL_VERSION_MAJOR EQUAL 2 )
        message ( FATAL_ERROR "${PROJECT_NAME} - unsupported OpenGL major-version, configuration required." )
    endif ( BT_GL_VERSION_MAJOR EQUAL 2 )

    if ( BT_GL_VERSION_MINOR EQUAL 0 )
        add_definitions ( -DBT_GL_MINOR=0 )
    elseif ( BT_GL_VERSION_MINOR EQUAL 1 )
        add_definitions ( -DBT_GL_MINOR=1 )
    elseif ( BT_GL_VERSION_MINOR EQUAL 2 )
        add_definitions ( -DBT_GL_MINOR=2 )
    elseif ( BT_GL_VERSION_MINOR EQUAL 3 )
        add_definitions ( -DBT_GL_MINOR=3 )
    else ( BT_GL_VERSION_MINOR EQUAL 0 )
        message ( FATAL_ERROR "${PROJECT_NAME} - unsupported OpenGL minor-version, configuration required." )
    endif ( BT_GL_VERSION_MINOR EQUAL 0 )

    if ( BT_OPEN_GL_ES )
        add_definitions ( -DBT_OPEN_GL_ES=1 )
        if ( BT_CMAKE_DEBUG )
            message ( STATUS "${PROJECT_NAME} - ES enabled." )
        endif ( BT_CMAKE_DEBUG )
    endif ( BT_OPEN_GL_ES )

    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - OpenGL ${BT_GL_VERSION_MAJOR}.${BT_GL_VERSION_MINOR} enabled." )
    endif ( BT_CMAKE_DEBUG )
elseif ( BT_VULKAN ) # Vulkan API

    message ( FATAL_ERROR "${PROJECT_NAME} - Vulkan API configuration required." )

    if ( NOT BT_VK_MAJOR OR NOT BT_VK_MINOR )
        message ( FATAL_ERROR "${PROJECT_NAME} - Vulkan version required, set <BT_VK_MAJOR> & <BT_VK_MINOR>." )
    endif ( NOT BT_VK_MAJOR OR NOT BT_VK_MINOR )

    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - Vulkan enabled." )
    endif ( BT_CMAKE_DEBUG )
else ( BT_OPEN_GL )
    message ( FATAL_ERROR "${PROJECT_NAME} - Renderer API not set !" )
endif ( BT_OPEN_GL )

# - - - - - - - - - - - - - - - - - DEBUG - - - - - - - - - - - - - - - - - -

if ( BT_CMAKE_DEBUG )
    if ( BT_BUILD_SDK )
        message ( STATUS "${PROJECT_NAME} - SDK Build enabled." )
    endif ( BT_BUILD_SDK )

    if ( BT_TESTS )
        message ( STATUS "${PROJECT_NAME} - tests enabled." )
    endif ( BT_TESTS )

    if ( BT_BUILD_STATIC )
        add_definitions ( -DBT_STATIC=1 )
        message ( STATUS "${PROJECT_NAME} - STATIC build enabled." )
    endif ( BT_BUILD_STATIC )

    if ( BT_BUILD_SHARED )
        add_definitions ( -DBT_SHARED=1 )
        add_definitions ( -DBT_EXPORT=1 )
        message ( STATUS "${PROJECT_NAME} - SHARED build enabled." )
    endif ( BT_BUILD_SHARED )

    if ( BT_EXPORT_SOURCES )
        message ( STATUS "${PROJECT_NAME} - headers & sources exported." )
    endif ( BT_EXPORT_SOURCES )

endif ( BT_CMAKE_DEBUG )