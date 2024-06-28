/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:26:25 by databey           #+#    #+#             */
/*   Updated: 2024/06/28 14:43:35 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig_handler(int sig)
{
	(void) sig;
	if (get_utils().in_heredoc) {
		exit(1);	
	}
}

void r_line(char **line, t_utils *u, int *fd, char *file_name)
{
	*u = get_utils();
	*fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*line = readline(HEREDOC_PROMPT);
}


int	q_ex_dol(char *str)
{
	int	dol;
	int	z;
	int	q;
	int	qo;

	dol = find_dol(str);
	z = 0;
	q = 0;
	qo = 0;
	while (str[z])
	{
		if (str[z] == '\'' && !q)
			q = 1;
		else if (str[z] == '\'' && q && z > dol)
			qo = 1;
		z++;
	}
	return (qo);
}

int	q_ex(char *str, char c)
{
	int	z;
	int	q;
	int	qo;
	int	f;

	f = 0;
	z = 0;
	q = 0;
	qo = 0;
	while (str[z])
	{
		if (str[z] == c && z && !q)
			q = z;
		else if (str[z] == c && q)
			qo = 1;
		if (q && z > q && str[z] != c)
			f = 1;
		z++;
	}
	if (!qo || !f)
		q = 0;
	return (q);
}

void e_hdoc(t_lexeme *heredoc, int quotes, t_global *g, char *file_name)
{
	int		fd;
	char	*line;
	t_utils	u;
	
	r_line(&line, &u, &fd, file_name);
	while (line && ft_strncmp(heredoc->string, line,
			ft_strlen(heredoc->string)) && !u.stop_heredoc)
	{
		if (quotes == 0)
			line = expand_str(g, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	if (line)
		free(line);
	if (u.stop_heredoc)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}