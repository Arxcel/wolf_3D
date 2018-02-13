cmake_minimum_required(VERSION 3.9)
project(wolf3D)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
include_directories(include libft/include) # header directories
set(SOURCE_FILES
       src/main.c
       src/sdl.c
       src/sdl_hook.c
       src/ft_matrix33.c
       src/ft_vector2.c
       src/rotate_matrix.c
       src/create_texture_patterns.c
        ) # sources
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)
set(LSDL ${CMAKE_SOURCE_DIR}/frameworks/SDL2.framework/SDL2)
set(LSDLIMG ${CMAKE_SOURCE_DIR}/frameworks/SDL2_image.framework/SDL2_image)
set(LSDLTTF ${CMAKE_SOURCE_DIR}/frameworks/SDL2_ttf.framework/SDL2_ttf)

add_executable(wolf3D ${SOURCE_FILES})
target_link_libraries(wolf3D ${LIBFT} ${LSDL} ${LSDLIMG} ${LSDLTTF})
