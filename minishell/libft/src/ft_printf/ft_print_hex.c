/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:13:12 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:38:55 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static int	ft_put_hex(unsigned int num, const char format)
{
	int	n;

	if (num >= 16)
	{
		n = ft_put_hex(num / 16, format);
		if (n == -1)
			return (-1);
		n = ft_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			n = ft_putchar_len((num + '0'));
		else
		{
			if (format == 'x')
				n = ft_putchar_len((num - 10 + 'a'));
			if (format == 'X')
				n = ft_putchar_len((num - 10 + 'A'));
		}
		if (n == -1)
			return (-1);
	}
	return (0);
}

int	ft_print_hex(unsigned int num, const char format)
{
	int	n;

	if (num == 0)
		return (ft_putchar_len('0'));
	else
		n = ft_put_hex(num, format);
	if (n == -1)
		return (n);
	return (ft_hex_len(num));
}
