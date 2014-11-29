project(test-cppcms)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")

find_package(CppCms REQUIRED)
include_directories(${CppCms_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CppCms_LIBRARIES})


target_link_libraries(test-cppcms ${LIBS})
