/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:40:02 by databey           #+#    #+#             */
/*   Updated: 2024/06/16 19:17:13 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include "errors.h"
# include "constants.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_tokens
{
	PIPE = 1,
	LESSER,
	LESSER_LESSER,
	GREATER,
	GREATER_GREATER,
}	t_tokens;

typedef struct s_lexer
{
	struct s_lexer	*next;
	struct s_lexer	*previous;
	char			*string;
	t_tokens		token;
	int				i;
}	t_lexeme;
    
typedef struct s_global
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lexeme				*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	int					heredoc;
	int					reset;
} t_global;

typedef struct s_utils
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_utils;

t_utils	g_utils;

t_lexeme	*new_lexeme(char *str, int token);
char		**arrdup(char **arr);
void		lexer_addback(t_lexeme **lst, t_lexeme *new);
void		init_signals(void);
void    	fatal_error(int err_no);
int			find_matching_quote(char *line, int i, int *num_del, int del);
int			parse_environment(t_global *g);
int			skip_qwhitespace(int i, char *str, char q);
int			free_global(t_global *g);
int			print_error(int err_no, t_global *g);
int			count_quotes(char *line);
int			setup_global(t_global *g);
int			find_pwd(t_global *g);
int			is_whitespace(char c);
int			parse_token(char *str, int i, t_lexeme **lexer_list);
int			skip_qwhitespace(int i, char *str, char del);
int			skip_spaces(char *str, int i);
int			add_node(char *str, t_tokens token, t_lexeme **lexeme_list);
int			read_words(int i, char *str, t_lexeme **lexeme_list);
int			token_reader(t_global *g);
int			lifecycle(t_global *g);

t_tokens	check_token(int c);


#endif