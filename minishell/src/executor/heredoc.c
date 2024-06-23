/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:42:39 by muyucego      #+#    #+#             */
/*   Updated: 2024/06/24 00:38:48 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_lexeme *heredoc, int quotes,
	t_global *g, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_PROMT);
	while (line && ft_strncmp(heredoc->string, line, ft_strlen(heredoc->string))
		&& !g_utils.stop_heredoc)
	{
		if (quotes == 0)
			line = expander_str(g, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMT);
	}
	free(line);
	if (g_utils.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	heredoc(t_global *g, t_lexeme *heredoc, char *file_name)
{
	int	quotes;
	int		sl;

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
	g_utils.stop_heredoc = 0;
	g_utils.in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, g, file_name);
	g_utils.in_heredoc = 0;
	g->heredoc = 1;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_global *g, t_commands  *cmd)
{
	t_lexeme	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{	
		if (cmd->redirections->token == LESSER_LESSER)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(g, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				g_utils.error_num = 1;
				return (reset_g(g));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
