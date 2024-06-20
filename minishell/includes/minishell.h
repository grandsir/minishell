/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:40:02 by databey           #+#    #+#             */
/*   Updated: 2024/06/20 18:33:46 by muyucego         ###   ########.fr       */
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
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>


t_commands	*commands_first(t_commands *map);
t_commands	*new_command(char **str, int num_redir, t_lexeme *redir);
t_lexeme	*new_lexeme(char *str, int token);
char		**arrdup(char **arr);
void		command_remove_first(t_commands **lst);
void		command_add_back(t_commands **lst, t_commands *new);
void		commands_clear(t_commands **lst);
void		count_pipes(t_lexeme *lexeme_list, t_global *global);
void		lexer_addback(t_lexeme **lst, t_lexeme *new);
void		init_signals(void);
void		parser_error(int error, t_global *g, t_lexeme *lexeme_list);
void  		fatal_error(int err_no);
void		ft_lexemeclear(t_lexeme **lst);
void		ft_lexemedelone(t_lexeme **lst, int key);
int			(*builtin(char *str))(t_global *g, t_commands *cmd);
int			find_matching_quote(char *line, int i, int *num_del, int del);
int			handle_pipe_errors(t_global *g, t_tokens token);
int			parse_environment(t_global *g);
int			skip_qwhitespace(int i, char *str, char q);
int			add_new_redirection(t_lexeme *tmp, t_parser_utils *parser_utils);
int			free_global(t_global *g);
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
int 		parser(t_global *g);
int			parser_token_error(t_global *g, t_lexeme *lexeme_list, t_tokens token);
int			print_error(int err_no, t_global *g);




t_tokens	check_token(int c);


#endif