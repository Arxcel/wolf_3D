cmake_minimum_required(VERSION 3.9)
project(wolf3D)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
include_directories(include libft/include) # header directories
set(SOURCE_FILES
       main.c
        src/cl_create_compile_program.c
        src/cl_create_input.c
        src/cl_create_kernel.c
        src/cl_create_queue.c
        src/cl_err_message.c
        src/cl_execute_kernel.c
        src/cl_set_args.c
        src/cl_create_context.c
        src/cl_get_platforms.c
        src/cl_get_devices.c
        src/cl_init.c
        ) # sources
find_package(OpenCL REQUIRED)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(wolf3D ${SOURCE_FILES})
target_link_libraries(wolf3D ${LIBFT} OpenCL::OpenCL)
