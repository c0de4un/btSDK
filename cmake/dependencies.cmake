# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
#
# btEngine Dependencies
#
# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - GLM - - - - - - - - - - - - - - - - - - - - - -

if ( NOT GLM_LIB_DIR )
    message ( FATAL_ERROR "${PROJECT_NAME} - GLM location not set ! GLM required for math !" )
endif ( NOT GLM_LIB_DIR )

if ( NOT EXISTS "${GLM_LIB_DIR}/glm/glm.hpp" )
    message ( FATAL_ERROR "${PROJECT_NAME} - GLM not found at #${GLM_LIB_DIR}" )
else ( NOT EXISTS "${GLM_LIB_DIR}/glm/glm.hpp" )
    if ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - GLM found at #${GLM_LIB_DIR}" )
    endif ( BT_CMAKE_DEBUG )
endif ( NOT EXISTS "${GLM_LIB_DIR}/glm/glm.hpp" )

# - - - - - - - - - - - - - - OpenGL (& ES) - - - - - - - - - - - - - - - - - - - -

if ( BT_OPEN_GL )

    if ( NOT EXISTS ${OpenGL} )
        message ( STATUS "${PROJECT_NAME} - OpenGL ES library not found !" )
    elseif ( BT_CMAKE_DEBUG )
        message ( STATUS "${PROJECT_NAME} - OpenGL found at ${OpenGL}, API ${BT_GL_VERSION_MAJOR}.${BT_GL_VERSION_MINOR}" )
    endif ( NOT EXISTS ${OpenGL} )

endif ( BT_OPEN_GL )


