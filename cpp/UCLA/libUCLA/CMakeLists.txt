set(the_target "libUCLA")

add_definitions(-Wall -std=c++0x)

file(GLOB p_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${the_target} ${p_src})

target_link_libraries(${the_target} ${LIBXS_LIBRARIES} ${JANSSON_LIBRARY})

