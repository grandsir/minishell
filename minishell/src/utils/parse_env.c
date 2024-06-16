/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:12:54 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/16 18:55:48 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_environment(t_global *g)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(g->envp);
	g->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (g->paths[i])
	{
		if (ft_strncmp(&g->paths[i][ft_strlen(g->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(g->paths[i], "/");
			free(g->paths[i]);
			g->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
