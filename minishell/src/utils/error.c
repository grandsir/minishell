/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:03:38 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/16 18:44:05 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    fatal_error(int err_no)
{
    if (err_no == MS_INVALID_ARG)
       printf("This program does not accept arguments\n");
    exit(0);
}

int    print_error(int err_no, t_global *g)
{
    if (err_no == MS_INVALID_ARG)
       printf("This program does not accept arguments\n");
    else if (err_no == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (err_no == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (err_no == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (err_no == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (err_no == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (err_no == 5)
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
