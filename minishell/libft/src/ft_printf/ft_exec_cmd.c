/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:27:23 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:38:53 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_exec_cmd(va_list *list, const char format)
{
	int	total;

	total = 0;
	if (format == 'c')
		total += ft_putchar_len(va_arg(*list, int));
	else if (format == 's')
		total += ft_putstr_len(va_arg(*list, char *));
	else if (format == 'p')
		total += ft_print_ptr(va_arg(*list, unsigned long long));
	else if (format == 'd' || format == 'i')
		total += ft_putnbr_len(va_arg(*list, int));
	else if (format == 'u')
		total += (ft_put_unsigned(va_arg(*list, unsigned int)));
	else if (format == 'x' || format == 'X')
		total += ft_print_hex(va_arg(*list, unsigned int), format);
	else if (format == '%')
		total += ft_putchar_len('%');
	return (total);
}
