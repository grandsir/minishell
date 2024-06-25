/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:54:19 by databey           #+#    #+#             */
/*   Updated: 2023/11/30 16:53:09 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_len(char *str)
{
	int	tmp;
	int	len;

	len = 0;
	if (str == NULL)
	{
		tmp = ft_putstr_len("(null)");
		if (tmp == -1)
			return (tmp);
		return (6);
	}
	while (*str)
	{
		tmp = ft_putchar_len(*str++);
		if (tmp == -1)
			return (-1);
		len++;
	}
	return (len);
}
