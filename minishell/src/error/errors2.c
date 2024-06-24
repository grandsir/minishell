/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:23:22 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/25 01:19:36 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_error(int error, t_global *g, t_lexeme *lexeme_list)
{
	ft_lexemeclear(&lexeme_list);
	print_error(error, g);
}

int	parser_token_error(t_global *g, t_lexeme *lexeme_list, t_tokens token)
{
	ft_putstr_fd("syntax error: next unexpected token ", STDERR_FILENO);
	if (token == GREATER)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREATER_GREATER)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESSER)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESSER_LESSER)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_lexemeclear(&lexeme_list);
	free_global(g);
	return (EXIT_FAILURE);
}

int	handle_pipe_errors(t_global *g, t_tokens token)
{
	if (token == PIPE)
	{
		parser_token_error(g, g->lexer_list, g->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!g->lexer_list)
	{
		parser_error(MS_INVALID_NEWLINE, g, g->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
