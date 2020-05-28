# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.options
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

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

set ( BT_PUBLIC_DIR "public/" )
set ( BT_PRIVATE_DIR "private/" )
set ( BIN_DIR "${CMAKE_SOURCE_DIR}/bin" )

option ( BT_CMAKE_DEBUG "Log-Output debug message about cmake-logic" ON )

option ( BT_BUILD_SDK "Build enabled SDK modules." ON )
option ( BT_TESTS "Unit testing" ON )
option ( BT_BUILD_STATIC "Build modules as STATIC libraries." ON )
option ( BT_BUILD_SHARED "Build modules as SHARED libraries." OFF )
option ( BT_EXPORT_SOURCES "Append all sources & headers to output-vars" OFF )

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