# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 00:37:08 by databey           #+#    #+#              #
#    Updated: 2024/06/16 20:24:07 by muyucego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LEXER_DIR = lexer/
UTILS_DIR = utils/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LIBFT_INCLUDE_DIR = ./libft/includes/

LEXER_DIR_FILES = token_reader handle_token
UTILS_DIR_FILES = error parse_env utils lexer_utils utils2

LEXER_FILES = $(addprefix $(LEXER_DIR), $(LEXER_DIR_FILES))
UTILS_FILES = $(addprefix $(UTILS_DIR), $(UTILS_DIR_FILES))

ORG_FILES = main lifecycle signals
SRC_FILES = $(addsuffix .c, $(ORG_FILES) $(LEXER_FILES) $(UTILS_FILES))
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))			
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
	
INCLUDES = $(READLINE_DIR)/include 

all: obj $(LIBFT) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)lexer/
	mkdir -p $(OBJ_DIR)utils/
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	gcc $(FLAGS) -I $(INCLUDES) -I $(INC_DIR) -I $(LIBFT) -o $@ -c $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	gcc $(OBJ) $(LIBFT) $(READLINE_LIB) -o $(NAME)

clean:
	rm -Rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
