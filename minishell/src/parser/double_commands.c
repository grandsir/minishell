/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:31:39 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/29 05:26:02 by databey          ###   ########.fr       */
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
	int			i;
	int			z;

	node = new_lexeme(ft_strdup(tmp->next->string), tmp->token);
	if (!node)
		parser_error(MS_MEMORY_FAILURE, parser_utils->g,
			parser_utils->lexer_list);
	lexer_addback(&parser_utils->redirections, node);
	i = tmp->i;
	z = tmp->next->i;
	ft_lexemedelone(&parser_utils->lexer_list, i);
	ft_lexemedelone(&parser_utils->lexer_list, z);
	parser_utils->num_redirections++;
	return (0);
}

void	rm_dcs(t_parser_utils *parser_utils)
{
	t_lexeme	*temp;

	temp = parser_utils->lexer_list;
	while (temp && temp->token == 0)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return ;
	if (!temp->next)
		parser_error(MS_INVALID_NEWLINE, parser_utils->g,
			parser_utils->lexer_list);
	if (temp->next->token)
		parser_token_error(parser_utils->g, parser_utils->lexer_list,
			temp->next->token);
	if ((temp->token >= GREATER && temp->token <= LESSER_LESSER))
		add_new_dc(temp, parser_utils);
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
