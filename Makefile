# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 04:21:55 by jestrada          #+#    #+#              #
#    Updated: 2022/08/31 15:40:26 by jarredon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

# src / obj files
SRC		=	main.c render.c render_utils.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

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
	mkdir -p $(OBJDIR)

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
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	make -C $(FT) fclean

r: all
	./$(NAME)

re: fclean
	$(MAKE)

.PHONY: re r fclean clean all
