/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:49:26 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/29 08:16:26 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

int	find_pwd(t_global *g)
{
	int	i;

	i = 0;
	while (g->envp[i])
	{
		if (!ft_strncmp(g->envp[i], "PWD=", 4))
			g->pwd = ft_substr(g->envp[i], 4, ft_strlen(g->envp[i]) - 4);
		if (!ft_strncmp(g->envp[i], "OLDPWD=", 7))
			g->old_pwd = ft_substr(g->envp[i], 7, ft_strlen(g->envp[i]) - 7);
		i++;
	}
	return (1);
}

int	count_quotes(char *line)
{
	size_t	i;
	int		s;
	int		d;

	s = 0;
	d = 0;
	i = 0;
	while ((i < ft_strlen(line)) && line[i])
	{
		if (line[i] == '"')
			i += find_matching_quote(line, i, &d, '"');
		if (line[i] == '\'')
			i += find_matching_quote(line, i, &s, '\'');
		i++;
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}

int	setup_global(t_global *g)
{
	g->cmds = NULL;
	g->lexer_list = NULL;
	g->reset = 0;
	g->pid = NULL;
	g->heredoc = 0;
	set_utils(NULL, 1);
	parse_environment(g);
	init_signals();
	return (1);
}
