/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:54:17 by databey           #+#    #+#             */
/*   Updated: 2024/06/29 07:59:52 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	free_g(t_global *g)
{
	free(g->args);
	commands_clear(&g->cmds);
	free_arr(g->paths);
	free_arr(g->envp);
	free(g->pwd);
	free(g->old_pwd);
	if (g->pipes)
		free(g->pid);
	rl_clear_history();
}

int	id(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	return_exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (id(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free_arr(str);
	exit(exit_code);
}

int	shell_exit(t_global *g, t_commands *cmd)
{
	char	**str;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = arrdup(cmd->str);
	free_g(g);
	return_exit_code(str);
	return (EXIT_SUCCESS);
}
