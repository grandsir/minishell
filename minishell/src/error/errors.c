/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:03:38 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 15:39:09 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    fatal_error(int err_no)
{
    if (err_no == MS_INVALID_ARG)
       printf("This program does not accept arguments\n");
    exit(0);
}

int		str_error(int err_no, char *error)
{
	if (err_no == MS_COMMAND_ERROR) {
		ft_putstr_fd("", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n\e[0;32m^\n\e[0;37m", STDERR_FILENO);
		ft_putstr_fd("\e[1;31merror:\e[0;37m command not found.\n", STDERR_FILENO);
	}
	else if (err_no == MS_EXPORT_ERROR) {
		if (error)
		{
			ft_putchar_fd('\'', STDERR_FILENO);
			ft_putstr_fd(error, STDERR_FILENO);
			ft_putstr_fd("\': is ", STDERR_FILENO);
		}
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (127);
}

int    print_error(int err_no, t_global *g)
{
    if (err_no == MS_INVALID_ARG)
       printf("This program does not accept arguments\n");
    else if (err_no == MS_INVALID_NEWLINE)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (err_no == MS_MEMORY_FAILURE)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (err_no == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (err_no == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (err_no == MS_PIPE_EXCEPTION)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (err_no == MS_FORK_FAILURE)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (err_no == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (err_no == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (err_no == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
    free_global(g);
    return (EXIT_FAILURE);
}
