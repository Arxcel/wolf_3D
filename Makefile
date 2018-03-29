# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/03 14:46:13 by vkozlov           #+#    #+#              #
#    Updated: 2018/03/29 15:39:38 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -O3

IDIR = ./include

CFLAGS = -I include \
		 -I libSDL/SDL2.framework/Headers \
		 -I libSDL/SDL2_image.framework/Headers 

LIBFT = libft

SDL2_F		= -framework SDL2 -framework SDL2_image -F ./libSDL/

SDL2_P		= -rpath @loader_path/libSDL/

DIR_S = src

DIR_O = obj

HEADER = include

_DEPS = ft_wolf.h

DEPS = $(patsubst %,$(HEADER)/%,$(_DEPS))

SOURCES =  main.c \
           sdl.c \
           sdl_hook.c \
           ft_matrix33.c \
           ft_vector2.c \
           utils.c \
           move_player.c \
           ray_cast.c \
           create_texture_patterns.c \
           ft_ftoa.c \
           floor_casting.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: obj $(NAME)

$(NAME): $(OBJS)
		make -C $(LIBFT)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS)  libft/libft.a $(SDL2_P) $(SDL2_F)

obj:
		mkdir -p obj

$(DIR_O)/%.o: $(DIR_S)/%.c $(DEPS)
		$(CC) -c -o $@ $< $(FLAGS) $(CFLAGS)

norme:
		make norme -C $(LIBFT)
		echo "--------------------Checking header files wolf3d"
		norminette ./$(HEADER)
		echo "--------------------Checking source files wolf3d"
		norminette ./$(DIR_S)

clean:
		rm -f $(OBJS)
		make clean -C $(LIBFT)
		rm -rf $(DIR_O)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, obj, norme, clean, fclean, re
.NOTPARALLEL:  all, obj, norme, clean, fclean, re
.SILENT: