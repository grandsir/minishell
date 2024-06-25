/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:51:24 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 14:57:39 by databey          ###   ########.fr       */
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

t_utils	get_utils(void)
{
	return (set_utils(NULL, 0));
}

t_utils	set_utils(t_utils *ut, int set)
{
	static t_utils	u;

	if (set != 0)
	{
		if (ut == NULL)
		{
			u.stop_heredoc = 0;
			u.in_cmd = 0;
			u.in_heredoc = 0;
		}
		else
		{
			u.error_num = ut->error_num;
			u.in_cmd = ut->in_cmd;
			u.in_heredoc = ut->in_heredoc;
			u.stop_heredoc = ut->stop_heredoc;
		}
	}
	return (u);
}

char	*expand_str(t_global *g, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[find_dol(str) - 2] != '\'' && find_dol(str) != 0
		&& str[find_dol(str)] != '\0')
	{
		tmp = detect_dollar_sign(g, str);
		free(str);
		str = tmp;
	}
	str = replace_q(str, '\"');
	str = replace_q(str, '\'');
	return (str);
}
