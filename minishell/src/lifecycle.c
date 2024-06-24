/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 03:56:15 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 17:07:08 by databey          ###   ########.fr       */
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
	signal(SIGQUIT, s_quit);
	g_utils.in_cmd = 1;
	if (g->pipes == 0)
		pipeless_cmd(g->cmds, g);
	else
	{
		g->pid = ft_calloc(sizeof(int), g->pipes + 2);
		if (!g->pid)
			return (print_error(MS_MEMORY_FAILURE, g));
		executor(g);
	}
	g_utils.in_cmd = 0;
	return (EXIT_SUCCESS);
}

char *get_prompt_str(t_global *g)
{
	char	*str;
	free(g->pwd);
	free(g->old_pwd);
	find_pwd(g);
	str = ft_strjoin(g->pwd, PROMPT);
	return (str);
}

int	lifecycle(t_global *g)
{
	char	*tmp;
	char	*s;

	s = get_prompt_str(g);
	g->args = readline(s);
	free(s);
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
	exec(g);
	free_global(g);
	return (1);
}