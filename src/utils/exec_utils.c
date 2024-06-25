/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:24:01 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/24 00:47:57 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_strjoin(char **s_str, char *str)
{
	char	*tmp;
	char	*add_space;
	int		i;

	tmp = ft_strdup(s_str[0]);
	i = 1;
	while (s_str[i])
	{
		str = tmp;
		add_space = ft_strjoin(str, " ");
		free(str);
		tmp = ft_strjoin(add_space, s_str[i]);
		free(add_space);
		i++;
	}
	str = tmp;
	return (str);
}

char	**resplit_str(char **double_arr)
{
	char	**ret;
	char	*joined_str;

	joined_str = ms_strjoin(double_arr, NULL);
	free_arr(double_arr);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	joined_str = ms_strjoin(ret, NULL);
	free_arr(ret);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	return (ret);
}
