/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:11:04 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:41:50 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (s + i);
	return (NULL);
}

char	*gnl_strdup(char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(*s1) * (gnl_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*gnl_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!str || !buff)
		return (NULL);
	s = malloc(sizeof(char) * ((gnl_strlen(str) + gnl_strlen(buff)) + 1));
	if (!s)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (str[++i] != '\0')
		s[i] = str[i];
	while (buff[j] != '\0')
		s[i++] = buff[j++];
	s[gnl_strlen(str) + gnl_strlen(buff)] = '\0';
	free(str);
	return (s);
}
