set(the_target "UCLA_Server")

add_definitions(-Wall -std=c++0x)
include_directories (${UCLA_SOURCE_DIR}/libUCLA)
link_directories (${UCLA_BINARY_DIR}/libUCLA) 

file(GLOB p_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${the_target} ${p_src})

target_link_libraries(${the_target} libUCLA)

