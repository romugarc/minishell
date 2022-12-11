/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:06:47 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/11 11:28:45 by rgarcia          ###   ########lyon.fr   */
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
		{
			printf("minishell: %s: Permission denied\n", (*cmd)[i].tab_outfile[j]);
			return (1);
		}
	}
	else
		*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*cmd)[i].append = 1;
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
			{
				printf("minishell: %s: Permission denied\n", (*cmd)[i].tab_outfile[j]);
				return (1);
			}
		}
		else
			*lastfd = open((*cmd)[i].tab_outfile[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd)[i].append = 0;
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

static int	create_fdnorm(t_commands **cmd, t_inc *i, int mode, t_envlist *envc)
{
	t_inc	inc;

	inc.i = i->i;
	if (mode == 1)
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_infile[inc.j] != 0)
		{
			if (create_fdin(cmd, inc, &(*i).lastfd, envc) == 1)
				return (1);
			inc.j++;
		}
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

int	create_fd(t_commands **cmd, int np, t_envlist *envc)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		inc.lastfd = -1;
		if ((*cmd)[inc.i].nb_infile > 0)
		{
			if (create_fdnorm(cmd, &inc, 1, envc) == 1)
				return (1);
		}
		else
			(*cmd)[inc.i].tab_fdin = NULL;
		(*cmd)[inc.i].fdin = inc.lastfd;
		inc.lastfd = -1;
		if ((*cmd)[inc.i].nb_outfile > 0)
		{
			if (create_fdnorm(cmd, &inc, 0, envc) == 1)
				return (1);
		}
		else
			(*cmd)[inc.i].tab_fdout = NULL;
		(*cmd)[inc.i].fdout = inc.lastfd;
	}
	return (0);
}
