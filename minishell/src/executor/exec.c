/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:09:50 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/29 06:01:19 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*expander_all(t_global *g, t_commands *cmd)
{
	t_lexeme	*start;

	cmd->str = expander(g, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESSER_LESSER)
			cmd->redirections->string = expand_str(g,
					cmd->redirections->string);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

int	wait_for_pipe(int *pid, int count)
{
	int		i;
	int		status;
	t_utils	u;

	i = 0;
	while (i < count)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
	{
		u = get_utils();
		u.error_num = WEXITSTATUS(status);
		set_utils(&u, 1);
	}
	return (EXIT_SUCCESS);
}

int	fork_multiple(t_global *g, int end[2], int in_fd, t_commands *cmd)
{
	static int	i = 0;

	if (g->reset == 1)
	{
		i = 0;
		g->reset = 0;
	}
	g->pid[i] = fork();
	if (g->pid[i] < 0)
		print_error(MS_FORK_FAILURE, g);
	if (g->pid[i] == 0)
		perform_dup(cmd, g, end, in_fd);
	i++;
	return (EXIT_SUCCESS);
}

int	check_heredoc(t_global *g, int end[2], t_commands *cmd)
{
	int	fd_in;

	if (g->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	executor(t_global *g)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (g->cmds)
	{
		g->cmds = expander_all(g, g->cmds);
		if (g->cmds->next)
			pipe(end);
		exec_hdoc(g, g->cmds);
		fork_multiple(g, end, fd_in, g->cmds);
		close(end[1]);
		if (g->cmds->prev)
			close(fd_in);
		fd_in = check_heredoc(g, end, g->cmds);
		if (g->cmds->next)
			g->cmds = g->cmds->next;
		else
			break ;
	}
	wait_for_pipe(g->pid, g->pipes);
	g->cmds = commands_first(g->cmds);
	return (0);
}
