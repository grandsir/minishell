/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:28:04 by databey           #+#    #+#             */
/*   Updated: 2024/06/27 16:44:33 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_lexeme *heredoc, int quotes, t_global *g, char *file_name)
{
	int 	pid;
	int 	status;
	
	pid = fork();
	if (pid == -1)
	{
		print_error(MS_FORK_FAILURE, g);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		e_hdoc(heredoc, quotes, g, file_name);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_global *g, t_lexeme *heredoc, char *file_name)
{
	int		quotes;
	int		sl;
	t_utils	u;

	u = get_utils();
	sl = EXIT_SUCCESS;
	if ((heredoc->string[0] == '\"'
			&& heredoc->string[ft_strlen(heredoc->string) - 1] == '\"')
		|| (heredoc->string[0] == '\''
			&& heredoc->string[ft_strlen(heredoc->string) - 1] == '\''))
		quotes = 1;
	else
		quotes = 0;
	replace_q(heredoc->string, '\"');
	replace_q(heredoc->string, '\'');
	u.stop_heredoc = 0;
	u.in_heredoc = 1;
	set_utils(&u, 1);
	sl = create_heredoc(heredoc, quotes, g, file_name);
	u = get_utils();
	u.in_heredoc = 0;
	set_utils(&u, 1);
	g->heredoc = 1;
	return (sl);
}

void	set_error_num(void)
{
	t_utils	u;

	u = get_utils();
	u.error_num = 1;
	set_utils(&u, 1);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("obj/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	exec_hdoc(t_global *g, t_commands *cmd)
{
	t_lexeme	*start;
	int			sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESSER_LESSER)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = heredoc(g, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				set_error_num();
				return (free_global(g));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
