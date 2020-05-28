# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine.options
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# DETECT LINUX
if ( NOT ANDROID AND UNIX AND NOT DEFINED LINUX AND NOT APPLE )

    # LINUX ON
    set ( LINUX ON )

endif ( NOT ANDROID AND UNIX AND NOT DEFINED LINUX AND NOT APPLE )

# PLATFORM
if ( ANDROID ) # ANDROID

    # Set Directory Prefix
    set ( PLATFORM_DIR "android" )
    add_definitions ( -DBT_ANDROID=1 )

elseif ( WIN32 OR WIN64 ) # WINDOWS

    # Set Directory Prefix
    set ( PLATFORM_DIR "windows" )
    add_definitions ( -DBT_WINDOWS=1 )
    add_definitions ( -DNOMINMAX )

elseif ( LINUX ) # LINUX

    # Set Directory Prefix
    set ( PLATFORM_DIR "linux" )
    add_definitions ( -DBT_LINUX=1 )

elseif ( APPLE ) # APPLE

    # Set Directory Prefix
    set ( PLATFORM_DIR "apple" )
    add_definitions ( -DBT_APPLE=1 )

else ( ANDROID ) # ?

    # ERROR
    message ( FATAL_ERROR "${PROJECT_NAME} - unknown platform ! Configuration required." )

    # Set Directory Prefix
    set ( PLATFORM_DIR "unix" )

endif ( ANDROID )

set ( PROJECT_BIN_OUTPUT_DIR "${BIN_DIR}/${PLATFORM_DIR}" )