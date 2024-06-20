/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:28:02 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/20 18:37:58 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum s_tokens
{
	PIPE = 1,
	GREATER,
	GREATER_GREATER,
	LESSER,
	LESSER_LESSER,
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
	struct s_commands		*cmds;
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

typedef struct s_parser_utils
{
	t_lexeme		*lexer_list;
	t_lexeme		*redirections;
	int				num_redirections;
	struct s_global	*g;
}	t_parser_utils;

typedef struct s_commands
{
	char					**str;
	int						(*builtin)(t_global*, struct s_commands *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexeme				*redirections;
	struct s_commands	*next;
	struct s_commands	*prev;
}	t_commands;

t_parser_utils	init_parser_utils(t_lexeme *lexer_list, t_global *global);
t_lexeme		*find_next_cmd(t_lexeme *lexer_lst);
void			rm_dcs(t_parser_utils *parser_utils);
void			count_pipes(t_lexeme *lexer_list, t_global *tools);
int				parse_envp(t_global *global);
int				find_pwd(t_global *global);
int				parser(t_global *global);
int				count_args(t_lexeme *lexer_list);
int				add_new_dc(t_lexeme *tmp, t_parser_utils *parser_tools);
int				handle_heredoc(t_parser_utils *parser_tools, t_lexeme *tmp);

#endif
