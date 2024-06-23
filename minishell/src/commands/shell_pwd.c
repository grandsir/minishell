/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:13:08 by muyucego      #+#    #+#             */
/*   Updated: 2024/06/23 22:32:03 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	shell_pwd(t_global *g, t_commands  *simple_cmd)
{
	(void) simple_cmd;
	ft_putendl_fd(g->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
