/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:58:21 by databey           #+#    #+#             */
/*   Updated: 2023/11/26 01:52:28 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_log10(int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		base;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	base = itoa_log10(n) + 1 + sign;
	str = (char *)malloc(base + 1);
	if (str == NULL)
		return (NULL);
	str[base] = '\0';
	while (base--)
	{
		str[base] = n % 10 + '0';
		n /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
