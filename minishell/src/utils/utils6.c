/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:45:30 by databey           #+#    #+#             */
/*   Updated: 2024/06/30 14:42:01 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_hdoc(char **line, int fd)
{
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	*line = readline(HEREDOC_PROMPT);
}
