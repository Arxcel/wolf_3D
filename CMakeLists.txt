cmake_minimum_required(VERSION 3.9)
project(wolf3D)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(SOURCE_FILES
       main.c) # sources
find_package(OpenCL REQUIRED)

add_executable(wolf3D ${SOURCE_FILES})
target_link_libraries(wolf3D OpenCL::OpenCL)
