# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 13:51:51 by tcharuel          #+#    #+#              #
#    Updated: 2024/01/05 11:40:24 by tcharuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEADER_DIR = includes
SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main.c draw.c utils.c hooks.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

MLX_DIR = ../minilibx

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wextra -Wall -Werror
RM = rm -f

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_DIR)/$(NAME).h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(HEADER_DIR)/ -c -o $@ $<

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -L$(MLX_DIR) -lft -lmlx -lXext -lX11 -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: $(NAME) all clean fclean re