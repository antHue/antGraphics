# Searches for ANTTWEAKBAR includes and library files
#
# Sets the variables
#   ANTTWEAKBAR_FOUND
#   ANTTWEAKBAR_INCLUDE_DIR
#   ANTTWEAKBAR_LIBRARY

SET (ANTTWEAKBAR_FOUND FALSE)

FIND_PATH (ANTTWEAKBAR_INCLUDE_DIR AntTweakBar.h
  /usr/include/AntTweakBar
  /usr/local/include/AntTweakBar
  /Users/anthonycouret/Developer/AntTweakBar/include/
  $ENV{HOME}/local/include/AntTweakBar
  )

FIND_LIBRARY (ANTTWEAKBAR_LIBRARY NAMES ANTTWEAKBAR PATHS
  /usr/lib
  /usr/local/lib
  /Users/anthonycouret/Developer/AntTweakBar/lib/
  $ENV{HOME}/local/lib
  )


IF (ANTTWEAKBAR_INCLUDE_DIR AND ANTTWEAKBAR_LIBRARY)
  SET (ANTTWEAKBAR_FOUND TRUE)
ENDIF (ANTTWEAKBAR_INCLUDE_DIR AND ANTTWEAKBAR_LIBRARY)

IF (ANTTWEAKBAR_LIBRARY)
  SET (ANTTWEAKBAR_LIBRARIES ${ANTTWEAKBAR_LIBRARY})
ENDIF(ANTTWEAKBAR_LIBRARY)

MARK_AS_ADVANCED (
  ANTTWEAKBAR_INCLUDE_DIR
  ANTTWEAKBAR_LIBRARIES
  ANTTWEAKBAR_LIBRARY  
)