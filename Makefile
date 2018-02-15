# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/03 14:46:13 by vkozlov           #+#    #+#              #
#    Updated: 2018/01/23 15:07:21 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror -O3

LIBFT = libft

SDL2_F		= -framework SDL2 -framework SDL2_image  -F ./frameworks/

SDL2_P		= -rpath ~/.brew/Cellar/
DIR_S = src

DIR_O = obj

HEADER = include

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
		@make -C $(LIBFT)
		@$(CC) -g $(FLAGS) -L $(LIBFT) -lft -o $(NAME) $^ $(SDL2_P) $(SDL2_F)

obj:
		@mkdir -p obj

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/ft_wolf.h
		@$(CC) -g $(FLAGS) -I $(HEADER) -c -o $@ $<

norme:
		@make norme -C $(LIBFT)
		@echo "--------------------Checking header files wolf3d"
		@norminette ./$(HEADER)
		@echo "--------------------Checking source files wolf3d"
		@norminette ./$(DIR_S)

clean:
		@rm -f $(OBJS)
		@make clean -C $(LIBFT)
		@rm -rf $(DIR_O)

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, obj, norme, clean, fclean, re
.NOTPARALLEL:  all, obj, norme, clean, fclean, re