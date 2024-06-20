# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 00:37:08 by databey           #+#    #+#              #
#    Updated: 2024/06/20 18:36:21 by muyucego         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LEXER_DIR = lexer/
PARSER_DIR = parser/
ERROR_DIR = error/
UTILS_DIR = utils/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LIBFT_INCLUDE_DIR = ./libft/includes/

LEXER_DIR_FILES = tokenizer parse_token
PARSER_DIR_FILES = parser double_commands
UTILS_DIR_FILES = parse_env utils lexer_utils utils2 command_utils builtin lexer_clear 
ERROR_DIR_FILES = errors errors2

LEXER_FILES = $(addprefix $(LEXER_DIR), $(LEXER_DIR_FILES))
UTILS_FILES = $(addprefix $(UTILS_DIR), $(UTILS_DIR_FILES))
PARSER_FILES = $(addprefix $(PARSER_DIR), $(PARSER_DIR_FILES))
ERROR_FILES = $(addprefix $(ERROR_DIR), $(ERROR_DIR_FILES))

ORG_FILES = main lifecycle signals
SRC_FILES = $(addsuffix .c, $(ORG_FILES) $(LEXER_FILES) $(UTILS_FILES) $(PARSER_FILES) $(ERROR_FILES))
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
	mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	mkdir -p $(OBJ_DIR)$(PARSER_DIR)
	mkdir -p $(OBJ_DIR)$(ERROR_DIR)
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
