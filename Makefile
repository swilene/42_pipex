# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saguesse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 14:54:21 by saguesse          #+#    #+#              #
#    Updated: 2022/11/08 14:13:34 by saguesse         ###   ########.fr        #
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
	pipex.c \
	clear.c \
	child_process.c \
	parent_process.c \

BONUS_SRC := main_bonus.c \
	path_bonus.c \
	init_files_bonus.c \
	init_cmds_bonus.c \
	init_heredoc_bonus.c \
	pipex_bonus.c \
	clear_bonus.c \
	child_process_bonus.c \
	parent_process_bonus.c \

HEADER = pipex.h

HEADER_BONUS = pipex_bonus.h

HEADER_LIBFT = $(LIBFT_PATH)/libft.h

HEADER_PRINTF = $(PRINTF_PATH)/libftprintf.h

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

$(NAME): $(PRINTF) $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF)

bonus: $(BONUS_OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(PRINTF)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(PRINTF):
	make -C $(PRINTF_PATH)

%.o : %.c $(HEADER) $(HEADER_BONUS) $(HEADER_LIBFT) $(HEADER_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@ -I . -I libft -I libft/ft_printf

all: $(NAME) 

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: bonus all clean fclean re
