# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saguesse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 14:54:21 by saguesse          #+#    #+#              #
#    Updated: 2022/11/03 14:10:46 by saguesse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc -g3

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

PRINTF_PATH = ./libft/ft_printf

PRINTF = $(PRINTF_PATH)/libftprintf.a

SRC = main.c \
	path.c \
	init_files.c \
	init_cmds.c \
	init_heredoc.c \
	pipex.c \
	clear.c \
	child_process.c \
	parent_process.c \

HEADER = pipex.h

HEADER_LIBFT = $(LIBFT_PATH)/libft.h

HEADER_PRINTF = $(PRINTF_PATH)/libftprintf.h

OBJ = $(SRC:.c=.o)

$(NAME): $(PRINTF) $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(PRINTF):
	make -C $(PRINTF_PATH)

%.o : %.c $(HEADER) $(HEADER_LIBFT) $(HEADER_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@ -I . -I libft -I libft/ft_printf

all: $(NAME) 

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
