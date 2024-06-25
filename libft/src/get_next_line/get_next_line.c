/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:10:52 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:41:50 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	check_newline(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (1);
	return (0);
}

char	*get_lines(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1 + check_newline(str)));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*update_str(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] && str)
	{
		free(str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (gnl_strlen(str) - i + 1));
	if (!s)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		z;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	z = 1;
	while (!gnl_strchr(str, '\n') && z != 0)
	{
		z = read(fd, buff, BUFFER_SIZE);
		if ((z <= 0 && !str) || z == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		buff[z] = '\0';
		if (!str && buff)
			str = gnl_strdup(buff);
		else
			str = gnl_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(str);
		return (0);
	}
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	line = get_lines(str);
	str = update_str(str);
	return (line);
}
