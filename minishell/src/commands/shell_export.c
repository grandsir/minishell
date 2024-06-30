/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:07:21 by databey           #+#    #+#             */
/*   Updated: 2024/06/30 12:23:08 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	variable_exist(t_global *g, char *str)
{
	int	i;

	i = 0;
	if (str[chr_sign(str)] == '\"')
		replace_q(str, '\"');
	if (str[chr_sign(str)] == '\'')
		replace_q(str, '\'');
	while (g->envp[i])
	{
		if (ft_strncmp(g->envp[i], str, chr_sign(g->envp[i])) == 0)
		{
			free(g->envp[i]);
			g->envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (str_error(MS_EXPORT_ERROR, str));
	if (chr_sign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (str_error(MS_EXPORT_ERROR, str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (str_error(MS_EXPORT_ERROR, str));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
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

char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[chr_sign(str)] == '\"')
		replace_q(str, '\"');
	if (str[chr_sign(str)] == '\'')
		replace_q(str, '\'');
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	shell_export(t_global *g, t_commands *cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmd->str[1] || cmd->str[1][0] == '\0')
		shell_env(g, cmd);
	else
	{
		while (cmd->str[i])
		{
			if (check_parameter(cmd->str[i]) == 0 && variable_exist(g,
					cmd->str[i]) == 0)
			{
				if (cmd->str[i])
				{
					tmp = add_var(g->envp, cmd->str[i]);
					free_arr(g->envp);
					g->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
