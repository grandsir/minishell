/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:34:11 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/16 18:38:44 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexeme	*new_lexeme(char *str, int token)
{
	t_lexeme		*new_lexeme;
	static int	i = 0;

	new_lexeme = (t_lexeme *)malloc(sizeof(t_lexeme));
	if (!new_lexeme)
		return (0);
	new_lexeme->string = str;
	new_lexeme->token = token;
	new_lexeme->i = i++;
    new_lexeme->previous = NULL;
	new_lexeme->next = NULL;
	return (new_lexeme);
}

void	lexer_addback(t_lexeme **lst, t_lexeme *new)
{
	t_lexeme	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}