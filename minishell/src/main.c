/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:39:38 by databey           #+#    #+#             */
/*   Updated: 2024/06/23 22:52:36 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_global g;

	if (argc != 1 || argv[1])
		fatal_error(MS_INVALID_ARG);
	g.envp = arrdup(envp);
	find_pwd(&g);
	setup_global(&g);
	lifecycle(&g);
}
