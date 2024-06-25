/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 22:49:05 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 14:23:51 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_change(t_global *g)
{
	char	*tmp;

	tmp = ft_strdup(g->pwd);
	free(g->old_pwd);
	g->old_pwd = tmp;
	free(g->pwd);
	g->pwd = getcwd(NULL, sizeof(NULL));
}

int	qm(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(get_utils().error_num);
	return (ft_strlen(*tmp) + 1);
}

size_t	chr_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*replace_q_value(char *str)
{
	char	**split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_arr(split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_arr(split_quotes);
	return (str);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+' || c == '^'
		|| c == '%' || c == '#' || c == '@' || c == '!' || c == '~' || c == '='
		|| c == '-' || c == '?' || c == '&' || c == '*');
}
