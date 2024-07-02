/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:40:02 by databey           #+#    #+#             */
/*   Updated: 2024/06/30 14:41:46 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "constants.h"
# include "errors.h"
# include "parser.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

t_commands	*expander_all(t_global *g, t_commands *cmd);
t_commands	*commands_first(t_commands *map);
t_commands	*new_command(char **str, int num_redir, t_lexeme *redir);
t_lexeme	*new_lexeme(char *str, int token);
t_tokens	check_token(int c);
t_utils		get_utils(void);
t_utils		set_utils(t_utils *ut, int set);
size_t		chr_sign(char *str);
size_t		find_dol(char *str);
char		**arrdup(char **arr);
char		**resplit_str(char **double_arr);
char		**expander(t_global *g, char **str);
char		*replace_q(char *str, char c);
char		*expand_str(t_global *g, char *str);
char		*detect_dollar_sign(t_global *g, char *str);
char		*cstr(char c);
char		*ms_strjoin(char **s_str, char *str);
void		perform_dup(t_commands *cmd, t_global *g, int end[2], int in_fd);
void		pipeless_cmd(t_commands *cmd, t_global *g);
void		command_remove_first(t_commands **lst);
void		command_add_back(t_commands **lst, t_commands *new);
void		commands_clear(t_commands **lst);
void		count_pipes(t_lexeme *lexeme_list, t_global *global);
void		lexer_addback(t_lexeme **lst, t_lexeme *new);
void		init_signals(void);
void		e_hdoc(t_lexeme *heredoc, int quotes, t_global *g, char *file_name);
void		heredoc_sig_handler(int sig);
void		s_quit(int sig);
void		free_g(t_global *g);
void		parser_error(int error, t_global *g, t_lexeme *lexeme_list);
void		fatal_error(int err_no);
void		ft_lexemeclear(t_lexeme **lst);
void		ft_lexemedelone(t_lexeme **lst, int key);
void		path_change(t_global *g);
void		print_hdoc(char **line, int fd);
int			q_ex(char *str, char c);
int			q_ex_dol(char *str);
int			(*builtin(char *str))(t_global *g, t_commands *cmd);
int			exec_hdoc(t_global *g, t_commands *cmd);
int			find_matching_quote(char *line, int i, int *num_del, int del);
int			handle_pipe_errors(t_global *g);
int			parse_environment(t_global *g);
int			skip_qwhitespace(int i, char *str, char q);
int			free_global(t_global *g);
int			count_quotes(char *line);
int			setup_global(t_global *g);
int			find_pwd(t_global *g);
int			str_error(int err_no, char *error);
int			chr_dol(char *str, int j);
int			is_whitespace(char c);
int			parse_token(char *str, int i, t_lexeme **lexer_list);
int			skip_qwhitespace(int i, char *str, char del);
int			skip_spaces(char *str, int i);
int			add_node(char *str, t_tokens token, t_lexeme **lexeme_list);
int			read_words(int i, char *str, t_lexeme **lexeme_list);
int			token_reader(t_global *g);
int			lifecycle(t_global *g);
int			parser(t_global *g);
int			parser_token_error(t_global *g, t_lexeme *lexeme_list,
				t_tokens token);
int			qm(char **tmp);
int			check_redir(t_commands *cmd);
int			check_fd_in(char *file);
int			check_fd_out(t_lexeme *redirection);
int			check_greater_greater(t_lexeme *redir);
int			wait_for_pipe(int *pid, int count);
int			fork_multiple(t_global *g, int end[2], int in_fd, t_commands *cmd);
int			check_heredoc(t_global *g, int end[2], t_commands *cmd);
int			executor(t_global *g);
int			replace_dollar(t_global *g, char *str, char **tmp, int j);
int			skip_if_number(int j, char *str);
int			print_error(int err_no, t_global *g);
int			shell_echo(t_global *g, t_commands *cmd);
int			shell_cd(t_global *g, t_commands *cmd);
int			shell_pwd(t_global *g, t_commands *cmd);
int			shell_export(t_global *g, t_commands *cmd);
int			shell_unset(t_global *g, t_commands *cmd);
int			shell_env(t_global *g, t_commands *cmd);
int			shell_exit(t_global *g, t_commands *cmd);
int			shell_continue(t_global *g, t_commands *cmd);
int			check_valid_identifier(char c);
int			check_cmd_path(t_commands *cmd, t_global *g);

#endif