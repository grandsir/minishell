/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 03:56:15 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/23 22:51:40 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_global(t_global *g)
{
	free(g->args);
	if (g->pid)
		free(g->pid);
	free_arr(g->paths);
	setup_global(g);
	g->reset = 1;
	lifecycle(g);
	return (1);
}

int	lifecycle(t_global *g)
{
	char	*tmp;

	g->args = readline(PROMPT);
	tmp = ft_strtrim(g->args, " ");
	free(g->args);
	g->args = tmp;
	if (!g->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (g->args[0] == '\0')
		return (free_global(g));
	add_history(g->args);
	if (!count_quotes(g->args))
		return (print_error(MS_INVALID_QUOTE, g));
	if (!token_reader(g))
		return (print_error(MS_MEMORY_FAILURE, g));
	parser(g);
	free_global(g);
	return (1);
}