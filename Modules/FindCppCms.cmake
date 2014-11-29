# - Try to find CppCms
# Once done this will define
#  CppCms_FOUND - System has CppCms
#  CppCms_INCLUDE_DIRS - The CppCms include directories
#  CppCms_LIBRARIES - The libraries needed to use CppCms
#  CppCms_DEFINITIONS - Compiler switches required for using CppCms

find_package(PkgConfig)
pkg_check_modules(PC_CppCms QUIET CppCms-1.0.5)
set(CppCms_DEFINITIONS ${PC_CppCms_CFLAGS_OTHER})

find_path(CppCms_INCLUDE_DIR cppcms/application.h
          HINTS ${PC_CppCms_INCLUDEDIR} ${PC_CppCms_INCLUDE_DIRS}
          PATH_SUFFIXES CppCms )

find_library(CppCms_LIBRARY NAMES cppcms
             HINTS ${PC_CppCms_LIBDIR} ${PC_CppCms_LIBRARY_DIRS} )

set(CppCms_LIBRARIES ${CppCms_LIBRARY} )
set(CppCms_INCLUDE_DIRS ${CppCms_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CppCms_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CppCms  DEFAULT_MSG
                                  CppCms_LIBRARY CppCms_INCLUDE_DIR)

mark_as_advanced(CppCms_INCLUDE_DIR CppCms_LIBRARY )
