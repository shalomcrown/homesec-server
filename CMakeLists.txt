project(homesec-server)
cmake_minimum_required(VERSION 2.8.3)
INCLUDE(CPack)

SET(MAJOR_VERSION "0")
SET(MINOR_VERSION "0")
SET(PATCH_VERSION "1")

aux_source_directory(src SRC_LIST)
file(GLOB_RECURSE TEMPLATES ${PROJECT_SOURCE_DIR}/*.tmpl)
file(GLOB_RECURSE STATIC_CONTENT ${PROJECT_SOURCE_DIR}/static/*)
include_directories(src)

find_program(TMPLCC cppcms_tmpl_cc)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")

find_package(CppCms REQUIRED)
find_package(MAGIC REQUIRED)
include_directories(${CppCms_INCLUDE_DIRS})

find_library(BOOSTER booster)


set(LIBS ${LIBS} ${CppCms_LIBRARIES} ${BOOSTER} ${MAGIC_LIBRARY} )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/login_details.cpp
    COMMAND ${TMPLCC}
        -d login_details_skin
                -o ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/login_details.cpp
        ${TEMPLATES}
    DEPENDS ${TEMPLATES})


add_library(login_details SHARED ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/login_details.cpp)

file(GLOB SOURCES "src/*.cpp" ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/login_details.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(homesec-server ${LIBS})

configure_file(homesec-server-config.js homesec-server-config.js COPYONLY)

file(COPY ${PROJECT_SOURCE_DIR}/src/static/ DESTINATION static)

# foreach(templateFile ${STATIC_CONTENT})
#         if(NOT IS_DIRECTORY ${templateFile})
#             message(STATUS "Configuring file ${templateFile}")
#             configure_file(${templateFile}  ${templateFile} COPYONLY)
#         endif(NOT IS_DIRECTORY ${templateFile})
# endforeach(templateFile)

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory
#                             ${CMAKE_SOURCE_DIR}/src/static ${PROJECT_BINARY_DIR})

INSTALL(PROGRAMS homesec-server DESTINATION local/share/homesec)
INSTALL(FILES homesec-server-config.js DESTINATION local/share/homesec)
INSTALL(FILES ${STATIC_CONTENT} DESTINATION local/share/homesec)


SET (CMAKE_PROJECT_NAME "homesec-server")

# autogenerate dependency information
IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_SET_DESTDIR "on")
SET(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)


SET(CPACK_PACKAGE_DESCRIPTION "Homesec server attempt with CppCms")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Trial server")
SET(CPACK_PACKAGE_CONTACT "shalomcrown@gmail.com")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
#demo dependencies
#SET(CPACK_DEBIAN_PACKAGE_DEPENDS " kate , plasma-desktop, libc6 (>= 2.1.3) ")

#SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA <yourpath_to>/postinst)

SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
#SET(CPACK_DEBIAN_PACKAGE_SECTION "kde")
SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")


add_subdirectory(src/static)
add_subdirectory(debian)
