/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:31:39 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 01:03:58 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_heredoc(char *str1, char *str2)
{
	char	*ret;
	char	*tmp;

	if (!str2)
		return (ft_strdup(str1));
	tmp = ft_strjoin(str1, " ");
	ret = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (ret);
}

int	add_new_dc(t_lexeme *tmp, t_parser_utils *parser_utils)
{
	t_lexeme	*node;
	int			index_1;
	int			index_2;

	node = new_lexeme(ft_strdup(tmp->next->string), tmp->token);
	if (!node)
		parser_error(MS_MEMORY_FAILURE, parser_utils->g,
			parser_utils->lexer_list);
	lexer_addback(&parser_utils->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexemedelone(&parser_utils->lexer_list, index_1);
	ft_lexemedelone(&parser_utils->lexer_list, index_2);
	parser_utils->num_redirections++;
	return (0);
}

void	rm_dcs(t_parser_utils *parser_utils)
{
	t_lexeme	*tmp;

	tmp = parser_utils->lexer_list;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		parser_error(MS_INVALID_NEWLINE, parser_utils->g,
			parser_utils->lexer_list);
	if (tmp->next->token)
		parser_token_error(parser_utils->g, parser_utils->lexer_list,
			tmp->next->token);
	if ((tmp->token >= GREATER && tmp->token <= LESSER_LESSER))
		add_new_dc(tmp, parser_utils);
	rm_dcs(parser_utils);
}

int	count_args(t_lexeme *lexer_list)
{
	t_lexeme	*tmp;
	int			i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
