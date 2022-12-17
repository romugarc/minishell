/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hd_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:33:57 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 19:15:19 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	hd_expand(char **lineh, t_envlist *env, t_heredoc *hd)
{
	if (expand_heredoc(lineh, env) == 1)
	{
		free(*lineh);
		return (1);
	}
	ft_putstr_fd(*lineh, hd->pipefd[1]);
	ft_putchar_fd('\n', hd->pipefd[1]);
	return (0);
}

int	hd_routine(t_cmd **c, t_inc inc, t_heredoc *hd, t_envlist *env)
{
	int		breaking;
	char	*lineh;

	signal(SIGINT, sig_heredoc);
	signal(SIGQUIT, sig_heredoc);
	breaking = 0;
	lineh = NULL;
	if (g_errno != -42)
		lineh = readline("> ");
	if (ft_strrcmp(lineh, (*c)[inc.i].tab_inf[inc.j]) == 0 && g_errno != -42)
	{
		free(lineh);
		breaking = 2;
	}
	else if (lineh != NULL && g_errno != -42)
	{
		if (hd_expand(&lineh, env, hd) == 1)
			return (1);
		free(lineh);
	}
	else if (lineh == NULL || g_errno == -42)
		breaking = 2;
	return (breaking);
}
