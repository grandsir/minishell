/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:53:42 by muyucego          #+#    #+#             */
/*   Updated: 2024/06/26 14:32:58 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	s_cmd(int sig)
{
	t_utils	u;

	u = get_utils();
	if (!u.in_heredoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (u.in_cmd)
	{
		u.stop_heredoc = 1;
		set_utils(&u, 1);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	s_quit(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, s_cmd);
	signal(SIGQUIT, SIG_IGN);
}
