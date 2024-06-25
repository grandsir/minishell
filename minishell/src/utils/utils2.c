/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:51:24 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 00:52:16 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

void	count_pipes(t_lexeme *lexeme_list, t_global *global)
{
	t_lexeme	*tmp;

	tmp = lexeme_list;
	global->pipes = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			global->pipes++;
		tmp = tmp->next;
	}
}
