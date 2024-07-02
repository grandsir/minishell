# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 00:37:08 by databey           #+#    #+#              #
#    Updated: 2024/06/30 14:51:05 by databey          ###   ########.fr        #
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
EXECUTOR_DIR = executor/
COMMANDS_DIR = commands/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LIBFT_INCLUDE_DIR = ./libft/includes/

LEXER_DIR_FILES = tokenizer parse_token
PARSER_DIR_FILES = parser double_commands
UTILS_DIR_FILES = parse_env utils utils2 utils3 utils4 utils5 utils6 lexer_utils command_utils builtin lexer_clear exec_utils
ERROR_DIR_FILES = errors errors2
EXECUTOR_DIR_FILES = check_redir exec execute_cmd expander heredoc
COMMANDS_DIR_FILES = shell_cd shell_echo shell_env shell_exit shell_export shell_pwd shell_unset 

LEXER_FILES = $(addprefix $(LEXER_DIR), $(LEXER_DIR_FILES))
UTILS_FILES = $(addprefix $(UTILS_DIR), $(UTILS_DIR_FILES))
PARSER_FILES = $(addprefix $(PARSER_DIR), $(PARSER_DIR_FILES))
ERROR_FILES = $(addprefix $(ERROR_DIR), $(ERROR_DIR_FILES))
EXECUTOR_FILES = $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_DIR_FILES))
COMMANDS_FILES = $(addprefix $(COMMANDS_DIR), $(COMMANDS_DIR_FILES))

ORG_FILES = main lifecycle signals
SRC_FILES = $(addsuffix .c, $(ORG_FILES) $(LEXER_FILES) $(UTILS_FILES) $(PARSER_FILES) $(ERROR_FILES) $(EXECUTOR_FILES) $(COMMANDS_FILES))
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))			
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

READLINE_LIB = -lreadline -lhistory 

all: obj $(LIBFT) $(NAME)

obj:
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	@ mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@ mkdir -p $(OBJ_DIR)$(PARSER_DIR)
	@ mkdir -p $(OBJ_DIR)$(ERROR_DIR)
	@ mkdir -p $(OBJ_DIR)$(EXECUTOR_DIR)
	@ mkdir -p $(OBJ_DIR)$(COMMANDS_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	cc $(FLAGS) -I $(INC_DIR) -I $(LIBFT) -o $@ -c $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	cc $(OBJ) $(LIBFT) $(READLINE_LIB) -o $(NAME)

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
