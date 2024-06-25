DOTC = ft_atoi ft_isalpha ft_itoa ft_memmove ft_putnbr_fd ft_strdup ft_strlcpy ft_strnstr ft_tolower \
ft_bzero ft_isascii ft_memchr ft_memset ft_putstr_fd ft_striteri ft_strlen ft_strrchr ft_toupper \
ft_calloc ft_isdigit ft_memcmp ft_putchar_fd ft_split ft_strjoin ft_strmapi ft_strtrim \
ft_isalnum ft_isprint ft_memcpy ft_putendl ft_strchr ft_strlcat ft_strncmp ft_substr

BONUS_DOTC = ft_lstnew ft_lstadd_front ft_lstlast ft_lstsize ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

EXTRA_FILES = ft_putchar_len ft_putstr_len ft_putnbr_len ft_log10
GNL_FILES = get_next_line_utils get_next_line
PRINTF_FILES = ft_exec_cmd ft_print_hex ft_print_ptr ft_printf ft_putunsigned

EXTRA_DIR = extra/
GNL_DIR = get_next_line/
PRINTF_DIR = ft_printf/
OBJECTS_DIR = objects/
INCLUDE_DIR = includes/
SRC_DIR = src/

DOTC+=$(addprefix $(EXTRA_DIR),$(EXTRA_FILES))
DOTC+=$(addprefix $(GNL_DIR), $(GNL_FILES))
DOTC+=$(addprefix $(PRINTF_DIR), $(PRINTF_FILES))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(DOTC)))
OBJ 		= 	$(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(DOTC)))
BONUS_OBJ	= 	$(addprefix $(OBJECTS_DIR), $(addsuffix .o, $(BONUS_DOTC)))

NAME = libft.a
CC = cc

CFLAGS = -Wall -Wextra -Werror -I

CREATE_OBJ = .cache_exists
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

$(OBJECTS_DIR)%.o : $(SRC_DIR)%.c | $(CREATE_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(CREATE_OBJ):
	@mkdir -p $(OBJECTS_DIR)
	@mkdir -p $(OBJECTS_DIR)$(EXTRA_DIR)
	@mkdir -p $(OBJECTS_DIR)$(GNL_DIR)
	@mkdir -p $(OBJECTS_DIR)$(PRINTF_DIR)

clean:
	@$(RM) -rf $(OBJECTS_DIR)
	@$(RM) -f $(OBJF)

fclean:		clean
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re