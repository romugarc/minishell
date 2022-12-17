/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:13:21 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 14:39:21 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	closefree_fdpipe(t_heredoc hd, int fdsave)
{
	dup2(hd.pipefd[1], fdsave);
	close(hd.pipefd[1]);
	close(hd.pipefd[0]);
	free(hd.pipefd);
	return (1);
}

static void	end_hd_prompt(t_heredoc hd, int fdsave, int *lfd)
{
	if (g_errno == -42)
		dup2(fdsave, 0);
	else
		dup2(hd.pipefd[1], fdsave);
	close(hd.pipefd[1]);
	close(fdsave);
	*lfd = hd.pipefd[0];
	free(hd.pipefd);
}

static int	heredoc_prompt(t_cmd **c, t_inc inc, int *lfd, t_envlist *envc)
{
	t_heredoc	hd;
	int			fdsave;
	int			ret;

	fdsave = dup(0);
	hd.pipefd = malloc(sizeof(int) * 2);
	if (pipe(hd.pipefd) == -1)
		return (1);
	while (1)
	{
		ret = hd_routine(c, inc, &hd, envc);
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		if (ret == 2)
			break ;
		else if (ret == 1)
			return (closefree_fdpipe(hd, fdsave));
	}
	end_hd_prompt(hd, fdsave, lfd);
	(*c)[inc.i].tab_fdin[inc.j] = *lfd;
	(*c)[inc.i].heredoc = 1;
	return (0);
}

int	create_fdin2(t_cmd **cmd, t_inc inc, int *lastfd, t_envlist *envc)
{
	if ((*cmd)[inc.i].flag_in[inc.j] == '1' && (*cmd)[inc.i].tab_fdin != NULL)
	{
		if (heredoc_prompt(cmd, inc, lastfd, envc) == 1)
			return (1);
	}
	else if ((*cmd)[inc.i].tab_fdin == NULL)
		return (1);
	return (0);
}

int	create_fdin(t_cmd **cmd, t_inc inc, int *lastfd)
{
	if ((*cmd)[inc.i].flag_in[inc.j] == '0' && (*cmd)[inc.i].tab_fdin != NULL)
	{
		if (access((*cmd)[inc.i].tab_inf[inc.j], F_OK) == 0)
		{
			if (access((*cmd)[inc.i].tab_inf[inc.j], R_OK) == 0)
				*lastfd = open((*cmd)[inc.i].tab_inf[inc.j], O_RDONLY);
			else
				return (1);
		}
		else
		{
			(*cmd)[inc.i].tab_fdin[inc.j] = *lastfd;
			return (1);
		}
		(*cmd)[inc.i].tab_fdin[inc.j] = *lastfd;
	}
	else if ((*cmd)[inc.i].tab_fdin == NULL)
		return (1);
	return (0);
}
