# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestrada <jestrada@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 04:21:55 by jestrada          #+#    #+#              #
#    Updated: 2022/09/05 19:02:26 by jestrada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

# src / obj files
SRC		=	main.c \
			render.c \
			render_utils.c \
			hook.c \
			hook_1.c \
			utils.c \
			qsort.c \
			sprites.c \
			parser/map/map_parser.c \
			parser/map/parser_checks.c \
			parser/map/parser_checks_1.c \
			parser/string_utils.c \
			parser/parser_rgb.c \
			parser/parser_utils.c \
			parser/header/parser_header.c \
			parser/header/parser_header1.c \
			parser/parser.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# MLX library
MLX		= ./MLX42
MLX_LIB	= $(addprefix $(MLX),mlx42.a)
MLX_INC	= -I $(MLX)/include 
MLX_LNK	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(MLX)/libmlx42.a

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(MLX_LIB) $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)/parser
	mkdir -p $(OBJDIR)/parser/map
	mkdir -p $(OBJDIR)/parser/header

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(MLX) clean
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(MLX) fclean
	make -C $(FT) fclean

r: all
	./$(NAME) ./map.cub

re: fclean
	$(MAKE)

.PHONY: re r fclean clean all
