/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:09:05 by muyucego      #+#    #+#             */
/*   Updated: 2024/06/23 22:32:03 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	shell_env(t_global *g, t_commands  *simple_cmd)
{
	int		i;

	(void) simple_cmd;
	i = 0;
	while (g->envp[i])
	{
		ft_putendl_fd(g->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
