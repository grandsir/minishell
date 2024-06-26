/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:05:17 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/26 15:58:21 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

int	shell_echo(t_global *g, t_commands *cmd)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 0;
	(void)g;
	while (cmd->str[i] && cmd->str[i][0] == '-' && cmd->str[i][1] == 'n')
	{
		j = 1;
		while (cmd->str[i][j] == 'n')
			j++;
		newline = 1;
		i++;
		break ;
	}
	print_lines(i, cmd->str, STDOUT_FILENO);
	if (newline == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
