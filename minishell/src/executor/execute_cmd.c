/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:24:04 by muyucego      #+#    #+#             */
/*   Updated: 2024/06/24 00:05:32 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_path(t_commands  *cmd, t_global *g)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, g->envp);
	while (g->paths[i])
	{
		mycmd = ft_strjoin(g->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, g->envp);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->str[0]));
}

void	execute_cmd(t_commands  *cmd, t_global *g)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(g, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0][0] != '\0')
		exit_code = check_cmd_path(cmd, g);
	exit(exit_code);
}

void	perform_dup(t_commands  *cmd, t_global *g, int end[2], int in_fd)
{
	if (cmd->prev && dup2(in_fd, STDIN_FILENO) < 0)
		ft_error(4, g);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, g);
	close(end[1]);
	if (cmd->prev)
		close(in_fd);
	execute_cmd(cmd, g);
}

void	pipeless_cmd(t_commands *cmd, t_global *g)
{
	int	pid;
	int	status;

	g->cmds = expander_all(g, g->cmds);
	if (cmd->builtin == shell_exit || cmd->builtin == shell_cd
		|| cmd->builtin == shell_unset || cmd->builtin == shell_export)
	{
		g_utils.error_num = cmd->builtin(g, cmd);
		return ;
	}
	send_heredoc(g, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, g);
	if (pid == 0)
		execute_cmd(cmd, g);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_utils.error_num = WEXITSTATUS(status);
}
