/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:06:47 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/14 17:03:04 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	create_fdout2(t_commands **cmd, int i, int j, int *lastfd)
{
	if (access((*cmd)[i].tab_outfile[j], F_OK) == 0)
	{
		if (access((*cmd)[i].tab_outfile[j], W_OK) == 0)
			*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_APPEND);
		else
			return (1);
	}
	else if ((*cmd)[i].tab_outfile[j][0] != '\0')
		*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*cmd)[i].append = 1;
	if ((*cmd)[i].tab_outfile[j][0] == '\0')
		return (1);
	return (0);
}

static int	create_fdout(t_commands **cmd, int i, int j, int *lastfd)
{
	if ((*cmd)[i].flag_out[j] == '0' && (*cmd)[i].tab_fdout != NULL)
	{
		if (access((*cmd)[i].tab_outfile[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_outfile[j], W_OK) == 0)
				*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_TRUNC);
			else
				return (1);
		}
		else if ((*cmd)[i].tab_outfile[j][0] != '\0')
			*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd)[i].append = 0;
		if ((*cmd)[i].tab_outfile[j][0] == '\0')
			return (1);
	}
	else if ((*cmd)[i].flag_out[j] == '1' && (*cmd)[i].tab_fdout != NULL)
	{
		if (create_fdout2(cmd, i, j, lastfd) == 1)
			return (1);
	}
	else if ((*cmd)[i].tab_fdout == NULL)
		return (1);
	(*cmd)[i].tab_fdout[j] = *lastfd;
	return (0);
}

static int	create_fdnormin(t_commands **cmd, t_inc *i, t_envlist *envc)
{
	t_inc	inc;
	int		ret;

	inc.i = i->i;
	inc.j = 0;
	while ((*cmd)[inc.i].tab_infile[inc.j] != 0)
	{
		ret = create_fdin(cmd, inc, &(*i).lastfd);
		if (ret == 1)
			break ;
		inc.j++;
	}
	inc.j = 0;
	while ((*cmd)[inc.i].tab_infile[inc.j] != 0)
	{
		if (create_fdin2(cmd, inc, &(*i).lastfd, envc) == 1)
			return (134);
		inc.j++;
	}
	if (ret == 1)
		return (1);
	return (0);
}

static int	create_fdnorm(t_commands **cmd, t_inc *i, int mode, t_envlist *envc)
{
	t_inc	inc;

	inc.i = i->i;
	(*i).l_e = 0;
	if (mode == 1)
	{
		(*i).l_e = create_fdnormin(cmd, i, envc);
		if ((*i).l_e != 0)
			return ((*i).l_e);
	}
	else
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_outfile[inc.j] != 0)
		{
			if (create_fdout(cmd, inc.i, inc.j, &(*i).lastfd) == 1)
				return (1);
			inc.j++;
		}
	}
	return (0);
}

static int	get_lastfd(t_commands cmd, int mode)
{
	int	lastfd;
	char	*cfd;

	if (mode == 1)
	{
		if (cmd.tab_fdin != NULL && cmd.nb_infile > 0)
		{
			cfd = ft_itoa(cmd.tab_fdin[cmd.nb_infile - 1]);
			lastfd = ft_atoi(cfd);
			free(cfd);
			return (lastfd);
		}
	}
	if (mode == 2)
	{
		if (cmd.tab_fdout != NULL && cmd.nb_outfile > 0)
		{
			cfd = ft_itoa(cmd.tab_fdout[cmd.nb_outfile - 1]);
			lastfd = ft_atoi(cfd);
			free(cfd);
			return (lastfd);
		}
	}
	return (1);
}

int	create_fd(t_commands **cmd, int np, t_envlist *envc)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		inc.lastfd = 1;
		if ((*cmd)[inc.i].nb_infile > 0)
		{
			if (create_fdnorm(cmd, &inc, 1, envc) == 134)
				return (134);
		}
		else
			(*cmd)[inc.i].tab_fdin = NULL;
		(*cmd)[inc.i].fdin = get_lastfd((*cmd)[inc.i], 1);
		inc.lastfd = 1;
		if ((*cmd)[inc.i].nb_outfile > 0)
		{
			if (create_fdnorm(cmd, &inc, 0, envc) == 134)
				return (134);
		}
		else
			(*cmd)[inc.i].tab_fdout = NULL;
		(*cmd)[inc.i].fdout = get_lastfd((*cmd)[inc.i], 2);
	}
	return (0);
}
