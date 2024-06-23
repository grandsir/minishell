/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:05:17 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 01:05:37 by muyucego         ###   ########.fr       */
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

int	shell_echo(t_global *g, t_commands  *simple_cmd)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = 0;
	(void) g;
	while (simple_cmd->str[i] && simple_cmd->str[i][0] == '-'
		&& simple_cmd->str[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->str[i][j] == 'n')
			j++;
		if (simple_cmd->str[i][j] == '\0')
			n_option = 1;
		else
			break ;
		i++;
	}
	print_lines(i, simple_cmd->str, STDOUT_FILENO);
	if (n_option == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
