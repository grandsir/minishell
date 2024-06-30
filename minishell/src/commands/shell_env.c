/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:54:10 by databey           #+#    #+#             */
/*   Updated: 2024/06/30 10:46:06 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_env(t_global *g, t_commands *cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	while (g->envp[i])
	{
		ft_putendl_fd(g->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
