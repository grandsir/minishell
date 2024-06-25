/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:53 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 01:02:34 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexeme	*ft_lexemeclear_one(t_lexeme **lst)
{
	if ((*lst)->string)
	{
		free((*lst)->string);
		(*lst)->string = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	ft_lexemedel_first(t_lexeme **lst)
{
	t_lexeme	*node;

	node = *lst;
	*lst = node->next;
	ft_lexemeclear_one(&node);
	if (*lst)
		(*lst)->previous = NULL;
}

void	ft_lexemedelone(t_lexeme **lst, int key)
{
	t_lexeme	*node;
	t_lexeme	*prev;
	t_lexeme	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_lexemedel_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->previous = prev;
	ft_lexemeclear_one(&node);
	*lst = start;
}

void	ft_lexemeclear(t_lexeme **lst)
{
	t_lexeme	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->string)
			free((*lst)->string);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
