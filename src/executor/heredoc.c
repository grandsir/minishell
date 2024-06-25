/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:28:04 by databey           #+#    #+#             */
/*   Updated: 2024/06/25 18:08:52 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_lexeme *heredoc, int quotes, t_global *g, char *file_name)
{
	int		fd;
	char	*line;
	t_utils	u;

	u = get_utils();
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_PROMPT);
	while (line && ft_strncmp(heredoc->string, line, ft_strlen(heredoc->string))
		&& !u.stop_heredoc)
	{
		if (quotes == 0)
			line = expand_str(g, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	free(line);
	if (u.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
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
