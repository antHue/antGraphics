# Searches for GLFW3 includes and library files
#
# Sets the variables
#   GLFW3_FOUND
#   GLFW3_INCLUDE_DIR
#   GLFW3_LIBRARY

SET (GLFW3_FOUND FALSE)

FIND_PATH (GLFW3_INCLUDE_DIR glfw3.h
  /usr/include/GLFW
  /usr/local/include/GLFW
  $ENV{HOME}/local/include/GLFW
  )

FIND_LIBRARY (GLFW3_LIBRARY NAMES GLFW3 PATHS
  /usr/lib
  /usr/local/lib
  $ENV{HOME}/local/lib
  )


IF (GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
  SET (GLFW3_FOUND TRUE)
ENDIF (GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)

IF (GLFW3_LIBRARY)
  SET (GLFW3_LIBRARIES ${GLFW3_LIBRARY})
ENDIF(GLFW3_LIBRARY)

MARK_AS_ADVANCED (
  GLFW3_INCLUDE_DIR
  GLFW3_LIBRARIES
  GLFW3_LIBRARY  
)