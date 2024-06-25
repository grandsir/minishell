/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:59:12 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 00:52:40 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_remove_first(t_commands **lst)
{
	t_commands	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	ft_lexemeclear(&(*lst)->redirections);
	free(*lst);
	*lst = tmp;
}

void	command_add_back(t_commands **lst, t_commands *new)
{
	t_commands	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_commands	*new_command(char **str, int num_redir, t_lexeme *redir)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (!new)
		return (0);
	new->str = str;
	new->builtin = builtin(str[0]);
	new->hd_file_name = NULL;
	new->num_redirections = num_redir;
	new->redirections = redir;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_commands	*commands_first(t_commands *map)
{
	int	i;

	i = 0;
	(void)i;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}

void	commands_clear(t_commands **lst)
{
	t_lexeme	*redir_tmp;
	t_commands	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redir_tmp = (*lst)->redirections;
		ft_lexemeclear(&redir_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
