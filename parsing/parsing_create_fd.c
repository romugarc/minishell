/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:06:47 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/29 16:51:52 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	create_fdin(t_commands **cmd, int i, int j, int *lastfd)
{
	if ((*cmd)[i].flag_in[j] == '0' && (*cmd)[i].tab_fdin != NULL)
	{
		if (access((*cmd)[i].tab_infile[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_infile[j], R_OK) == 0)
				*lastfd = open((*cmd)[i].tab_infile[j], O_RDONLY);
			else
			{
				printf("minishell: %s: Permission denied\n", (*cmd)[i].tab_infile[j]);
				return (1);
			}
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", (*cmd)[i].tab_infile[j]);
			return (1);
		}
		(*cmd)[i].heredoc = 0;
		(*cmd)[i].tab_fdin[j] = *lastfd;
	}
	else if ((*cmd)[i].flag_in[j] == '1' && (*cmd)[i].tab_fdin != NULL)
		(*cmd)[i].heredoc = 1;
	else if ((*cmd)[i].tab_fdin == NULL)
		return (1);
	return (0);
}

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

static int	create_fdnorminette(t_commands **cmd, int i, int *lastfd, int mode)
{
	int	j;

	if (mode == 1)
	{
		j = 0;
		while ((*cmd)[i].tab_infile[j] != 0)
		{
			if (create_fdin(cmd, i, j, lastfd) == 1)
				return (1);
			j++;
		}
	}
	else
	{
		j = 0;
		while ((*cmd)[i].tab_outfile[j] != 0)
		{
			if (create_fdout(cmd, i, j, lastfd) == 1)
				return (1);
			j++;
		}
	}
	return (0);
}

int	create_fd(t_commands **cmd, int np)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		inc.lastfd = -1;
		if ((*cmd)[inc.i].nb_infile > 0)
		{
			if (create_fdnorminette(cmd, inc.i, &inc.lastfd, 1) == 1)
				return (1);
		}
		else
			(*cmd)[inc.i].tab_fdin = NULL;
		(*cmd)[inc.i].fdin = inc.lastfd;
		inc.lastfd = -1;
		if ((*cmd)[inc.i].nb_outfile > 0)
		{
			if (create_fdnorminette(cmd, inc.i, &inc.lastfd, 0) == 1)
				return (1);
		}
		else
			(*cmd)[inc.i].tab_fdout = NULL;
		(*cmd)[inc.i].fdout = inc.lastfd;
	}
	return (0);
}
