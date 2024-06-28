/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:28:35 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/28 13:36:37 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_utils	init_parser_utils(t_lexeme *lexer_list, t_global *g)
{
	t_parser_utils	parser_utils;

	parser_utils.lexer_list = lexer_list;
	parser_utils.redirections = NULL;
	parser_utils.num_redirections = 0;
	parser_utils.g = g;
	return (parser_utils);
}

t_commands	*new_parser_command(t_parser_utils *parser_utils)
{
	int			i;
	int			argc;
	t_lexeme	*tmp;
	char		**str;

	i = 0;
	rm_dcs(parser_utils);
	argc = count_args(parser_utils->lexer_list);
	str = ft_calloc(argc + 1, sizeof(char *));
	if (!str)
		parser_error(MS_MEMORY_FAILURE, parser_utils->g,
			parser_utils->lexer_list);
	tmp = parser_utils->lexer_list;
	while (argc > 0)
	{
		if (tmp->string)
		{
			str[i++] = ft_strdup(tmp->string);
			ft_lexemedelone(&parser_utils->lexer_list, tmp->i);
			tmp = parser_utils->lexer_list;
		}
		argc--;
	}
	return (new_command(str, parser_utils->num_redirections,
			parser_utils->redirections));
}

int	parser(t_global *g)
{
	t_commands		*n;
	t_parser_utils	parser_utils;

	g->cmds = NULL;
	count_pipes(g->lexer_list, g);
	if (g->lexer_list->token == PIPE)
		return (parser_token_error(g, g->lexer_list,
				g->lexer_list->token));
	while (g->lexer_list)
	{
		if (g->lexer_list && g->lexer_list->token == PIPE)
			ft_lexemedelone(&g->lexer_list, g->lexer_list->i);
		if (handle_pipe_errors(g))
			return (EXIT_FAILURE);
		parser_utils = init_parser_utils(g->lexer_list, g);
		n = new_parser_command(&parser_utils);
		if (!n)
			parser_error(MS_INVALID_NEWLINE, g, parser_utils.lexer_list);
		if (!g->cmds)
			g->cmds = n;
		else
			command_add_back(&g->cmds, n);
		g->lexer_list = parser_utils.lexer_list;
	}
	return (EXIT_SUCCESS);
}
