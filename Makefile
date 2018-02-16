# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/03 14:46:13 by vkozlov           #+#    #+#              #
#    Updated: 2018/02/16 15:52:06 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -O3

IDIR = ./include

CFLAGS = -I$(IDIR)

LIBFT = libft

LSDL2 =  -L/Users/vkozlov/.brew/Cellar/sdl2/2.0.7/lib -lSDL2\
        -L/Users/vkozlov/.brew/Cellar/sdl2_image/2.0.2/lib -lSDL2_image

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
		$(CC) -o $(NAME) $(OBJS) $(FLAGS)  libft/libft.a $(LSDL2)

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