/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sig_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:44:26 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:37:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_errno = -42;
		close (0);
		printf("\n");
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cancel_sighandler(int signal)
{
	(void)signal;
}

void	pipe_sighandler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_errno = 1;
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
