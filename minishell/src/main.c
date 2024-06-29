/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:39:38 by databey           #+#    #+#             */
/*   Updated: 2024/06/29 07:53:48 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_global	g;

	if (argc != 1 || argv[1])
		fatal_error(MS_INVALID_ARG);
	g.envp = arrdup(envp);
	find_pwd(&g);
	setup_global(&g);
	lifecycle(&g);
}
