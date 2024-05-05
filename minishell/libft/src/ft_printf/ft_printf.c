/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:37:02 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:38:42 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		len;
	int		i;
	int		tmp;

	va_start(list, str);
	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
			tmp = ft_exec_cmd(&list, str[++i]);
		else
			tmp = ft_putchar_len(str[i]);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	va_end(list);
	return (len);
}
