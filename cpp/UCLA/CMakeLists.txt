project(UCLA)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LibXS REQUIRED)

if(UNIX)
    add_definitions(-DUCLA_HAVE_UNIX)
endif(UNIX)

add_subdirectory(libUCLA)
add_subdirectory(UCLA_Client)
add_subdirectory(UCLA_Server)

