/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:17:04 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 01:04:37 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_ret(char *str, t_global *g)
{
	int	i;

	i = 0;
	while (g->envp[i])
	{
		if (!ft_strncmp(g->envp[i], str, ft_strlen(str)))
			return (ft_substr(g->envp[i], ft_strlen(str),
					ft_strlen(g->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_global *g, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, g);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_global *g)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g->envp[i])
	{
		if (!ft_strncmp(g->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", g->pwd);
			free(g->envp[i]);
			g->envp[i] = tmp;
		}
		else if (!ft_strncmp(g->envp[i], "OLDPWD=", 7) && g->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", g->old_pwd);
			free(g->envp[i]);
			g->envp[i] = tmp;
		}
		i++;
	}
}

int	shell_cd(t_global *g, t_commands *cmd)
{
	int		ret;

	if (!cmd->str[1])
		ret = specific_path(g, "HOME=");
	else if (ft_strncmp(cmd->str[1], "-", 1) == 0)
		ret = specific_path(g, "OLDPWD=");
	else
	{
		ret = chdir(cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	path_change(g);
	add_path_to_env(g);
	return (EXIT_SUCCESS);
}
