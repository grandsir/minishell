/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:21:18 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/28 13:31:51 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}

int	add_node(char *str, t_tokens token, t_lexeme **lexeme_list)
{
	t_lexeme	*node;

	node = new_lexeme(str, token);
	if (!node)
		return (0);
	lexer_addback(lexeme_list, node);
	return (1);
}

int	read_words(int i, char *str, t_lexeme **lexeme_list)
{
	size_t	j;

	j = 0;
	while (i + j <= ft_strlen(str) && str[i + j] && !(check_token(str[i + j])))
	{
		j += skip_qwhitespace(i + j, str, '"');
		j += skip_qwhitespace(i + j, str, '\'');
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j + 1), 0, lexeme_list))
		return (-1);
	return (j);
}

int	token_reader(t_global *g)
{
	size_t	i;
	int		j;

	i = 0;
	while (i <= ft_strlen(g->args) && g->args[i])
	{
		j = 0;
		i += skip_spaces(g->args, i);
		if (check_token(g->args[i]))
			j = parse_token(g->args, i, &g->lexer_list);
		else
			j = read_words(i, g->args, &g->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
