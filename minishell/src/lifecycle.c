/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 03:56:15 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/27 14:08:55 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_global(t_global *g)
{
	free(g->args);
	commands_clear(&g->cmds);
	if (g->pid)
		free(g->pid);
	free_arr(g->paths);
	setup_global(g);
	g->reset = 1;
	lifecycle(g);
	return (1);
}

int	exec(t_global *g)
{
	t_utils	u;

	signal(SIGQUIT, s_quit);
	u = get_utils();
	u.in_cmd = 1;
	set_utils(&u, 1);
	if (g->pipes == 0)
		pipeless_cmd(g->cmds, g);
	else
	{
		g->pid = ft_calloc(sizeof(int), g->pipes + 2);
		if (!g->pid)
			return (print_error(MS_MEMORY_FAILURE, g));
		executor(g);
	}
	u = get_utils();
	u.in_cmd = 0;
	set_utils(&u, 1);
	return (EXIT_SUCCESS);
}

char	*get_prompt_str()
{
	char	*color;

	color = ft_strjoin(PROMPT_COLOR, PROMPT);
	return (color);
}

int	lifecycle_commands(t_global *g)
{
	if (!count_quotes(g->args))
		return (print_error(MS_INVALID_QUOTE, g));
	if (!token_reader(g))
		return (print_error(MS_MEMORY_FAILURE, g));
	parser(g);
	exec(g);
	free_global(g);
	return (1);
}

int	lifecycle(t_global *g)
{
	char	*tmp;
	char	*s;

	s = get_prompt_str();
	g->args = readline(s);
	free(s);
	if (!g->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	tmp = ft_strtrim(g->args, " ");
	free(g->args);
	if (!tmp)
		return (free_global(g));
	g->args = tmp;
	if (g->args[0] == '\0')
		return (free_global(g));
	add_history(g->args);
	return (lifecycle_commands(g));
}
