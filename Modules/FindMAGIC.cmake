#
#  Copyright (c) 2006-2009 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# $ sudo apt-get install libmagic-dev
# $ dpkg -L libmagic-dev
# ...
# /usr/include/magic.h
# /usr/lib/libmagic.so


find_path(MAGIC_INCLUDE_DIR magic.h /usr/local/include /usr/include /usr/include/linux )

FIND_LIBRARY(MAGIC_LIBRARY
  NAMES magic libmagic libmagic.so.1
  PATHS /usr/lib /usr/local/lib /usr/lib/i386-linux-gnu
  )

IF (MAGIC_LIBRARY AND MAGIC_INCLUDE_DIR)
    SET(MAGIC_LIBRARIES ${MAGIC_LIBRARY})
    SET(MAGIC_INCLUDE_DIRS ${MAGIC_INCLUDE_DIR} ${MAGIC_INCLUDE_DIR}/poppler)
    SET(MAGIC_FOUND "YES")
ELSE (MAGIC_LIBRARY AND MAGIC_INCLUDE_DIR)
  SET(MAGIC_FOUND "NO")
ENDIF (MAGIC_LIBRARY AND MAGIC_INCLUDE_DIR)


IF (MAGIC_FOUND)
   IF (NOT MAGIC_FIND_QUIETLY)
      MESSAGE(STATUS "Found MAGIC: ${MAGIC_LIBRARIES}")
   ENDIF (NOT MAGIC_FIND_QUIETLY)
ELSE (MAGIC_FOUND)
   IF (MAGIC_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find MAGIC library ${MAGIC_LIBRARY}  ${MAGIC_INCLUDE_DIR}" )
   ENDIF (MAGIC_FIND_REQUIRED)
ENDIF (MAGIC_FOUND)

MARK_AS_ADVANCED(
  MAGIC_LIBRARY
  MAGIC_INCLUDE_DIR
  )
