/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:54:03 by databey           #+#    #+#             */
/*   Updated: 2024/06/24 15:08:39 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_pwd(t_global *g, t_commands *cmd)
{
	(void)cmd;
	ft_putendl_fd(g->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
