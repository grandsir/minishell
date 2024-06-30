/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:39:57 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/30 12:23:20 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_greater_greater(t_lexeme *redir)
{
	int	fd;

	if (redir->token == GREATER_GREATER)
		fd = open(redir->string, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redir->string, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	check_fd_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_fd_out(t_lexeme *redirection)
{
	int	fd;

	fd = check_greater_greater(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redir(t_commands *cmd)
{
	t_lexeme	*start;

	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESSER)
		{
			if (check_fd_in(cmd->redirections->string))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == GREATER
			|| cmd->redirections->token == GREATER_GREATER)
		{
			if (check_fd_out(cmd->redirections))
				return (EXIT_FAILURE);
		}
		else if (cmd->redirections->token == LESSER_LESSER)
		{
			if (check_fd_in(cmd->hd_file_name))
				return (EXIT_FAILURE);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
