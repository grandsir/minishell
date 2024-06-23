/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:45:23 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 00:43:13 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*builtin(char *str))(t_global *g, t_commands *cmd)
{
	static void	*b[7][2] = {
	{"cd", shell_cd},
	{"env", shell_env},
	{"export", shell_export},
	{"unset", shell_unset},
	{"pwd", shell_pwd},
	{"echo", shell_echo},
	{"exit", shell_exit}
	};
	int			z;

	z = 0;
	while (z < 7)
	{
		if (str)
		{
			if (!ft_strncmp(b[z][0], str, ft_strlen((b[z][0]))))
				return (b[z][1]);
		}
		z++;
	}
	return (NULL);
}
