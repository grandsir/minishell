/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:42:49 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 01:17:38 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'>', GREATER},
	{'<', LESSER},
	{'|', PIPE},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	parse_token(char *str, int i, t_lexeme **lexer_list)
{
	t_tokens	token;

	token = check_token(str[i]);
	if (token == GREATER && check_token(str[i + 1]) == GREATER)
	{
		if (!add_node(NULL, GREATER_GREATER, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LESSER && check_token(str[i + 1]) == LESSER)
	{
		if (!add_node(NULL, LESSER_LESSER, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

int	skip_qwhitespace(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}
