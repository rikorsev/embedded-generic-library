cmake_minimum_required(VERSION 3.22.2 FATAL_ERROR)

project(egl_lib LANGUAGES C)

add_library(${PROJECT_NAME})

add_subdirectory(components)
add_subdirectory(hal)
add_subdirectory(drivers)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
