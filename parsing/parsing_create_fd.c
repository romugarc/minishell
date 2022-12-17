/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:06:47 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 16:49:46 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_lastfd(t_cmd cmd, int mode)
{
	int		lastfd;
	char	*cfd;

	if (mode == 1)
	{
		if (cmd.tab_fdin != NULL && cmd.nb_inf > 0)
		{
			cfd = ft_itoa(cmd.tab_fdin[cmd.nb_inf - 1]);
			lastfd = ft_atoi(cfd);
			free(cfd);
			return (lastfd);
		}
	}
	if (mode == 2)
	{
		if (cmd.tab_fdout != NULL && cmd.nb_outf > 0)
		{
			cfd = ft_itoa(cmd.tab_fdout[cmd.nb_outf - 1]);
			lastfd = ft_atoi(cfd);
			free(cfd);
			return (lastfd);
		}
	}
	return (1);
}

static int	create_fd2(t_cmd **cmd, t_envlist *envc, t_inc *inc)
{
	inc->lastfd = 1;
	if ((*cmd)[inc->i].nb_outf > 0)
	{
		if (create_fdnorm(cmd, inc, 0, envc) == 134)
			return (134);
	}
	else
		(*cmd)[inc->i].tab_fdout = NULL;
	return (0);
}

int	create_fd(t_cmd **cmd, int np, t_envlist *envc)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		inc.lastfd = 1;
		if ((*cmd)[inc.i].nb_inf > 0)
		{
			if (create_fdnorm(cmd, &inc, 1, envc) == 134)
				return (134);
		}
		else
			(*cmd)[inc.i].tab_fdin = NULL;
		if (g_errno == -42)
			return (-42);
		(*cmd)[inc.i].fdin = get_lastfd((*cmd)[inc.i], 1);
		if (create_fd2(cmd, envc, &inc) == 134)
			return (134);
		(*cmd)[inc.i].fdout = get_lastfd((*cmd)[inc.i], 2);
	}
	return (0);
}
