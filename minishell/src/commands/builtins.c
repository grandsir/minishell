/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 15:08:39 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*builtin_arr(char *str))(t_global *g, t_commands  *cmd)
{
	static void	*builtins[7][2] = {
	{"echo", shell_echo},
	{"cd", shell_cd},
	{"pwd", shell_pwd},
	{"export", shell_export},
	{"unset", shell_unset},
	{"env", shell_env},
	{"exit", shell_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}
