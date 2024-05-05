/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:37:12 by databey           #+#    #+#             */
/*   Updated: 2024/01/25 23:52:44 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_exec_cmd(va_list *args, const char format);
int	ft_print_hex(unsigned int num, const char format);
int	ft_put_unsigned(unsigned int n);
int	ft_print_ptr(unsigned long long num);

#endif