/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:13:21 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/14 20:33:02 by fsariogl         ###   ########.fr       */
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

static int	heredoc_routine(t_commands **cmd, t_inc inc, t_heredoc *hd, t_envlist *envc)
{
	int		breaking;
	char	*lineh;

	signal(SIGINT, sig_heredoc);
	signal(SIGQUIT, sig_heredoc);
	breaking = 0;
	lineh = NULL;
	if (g_errno != -42)
		lineh = readline("> ");
	if (ft_strrcmp(lineh, (*cmd)[inc.i].tab_infile[inc.j]) == 0 && g_errno != 42)
	{
		free(lineh);
		breaking = 2;
	}
	else if (lineh != NULL && g_errno != -42)
	{
		if (expand_heredoc(&lineh, envc) == 1)
		{
			free(lineh);
			return (1);
		}
		ft_putstr_fd(lineh, hd->pipefd[1]);
		ft_putchar_fd('\n', hd->pipefd[1]);
		free(lineh);
	}
	if (lineh == NULL || g_errno == -42)
		breaking = 2;
	return (breaking);
}

static int	heredoc_prompting(t_commands **cmd, t_inc inc, int *lastfd, t_envlist *envc)
{
	t_heredoc hd;
	int		fdsave;
	int		ret;

	fdsave = dup(0);
	hd.pipefd = malloc(sizeof(int) * 2);
	if (pipe(hd.pipefd) == -1)
		return (1);
	while (1)
	{
		ret = heredoc_routine(cmd, inc, &hd, envc);
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		if (ret == 2)
			break ;
		else if (ret == 1)
			return (closefree_fdpipe(hd, fdsave));
	}
	if (g_errno == -42)
		dup2(fdsave, 0);
	else
		dup2(hd.pipefd[1], fdsave);
	close(hd.pipefd[1]);
	close(fdsave);
	*lastfd = hd.pipefd[0];
	(*cmd)[inc.i].tab_fdin[inc.j] = *lastfd;
	(*cmd)[inc.i].heredoc = 1;
	free(hd.pipefd);
	return (0);
}

int	create_fdin2(t_commands **cmd, t_inc inc, int *lastfd, t_envlist *envc)
{
	if ((*cmd)[inc.i].flag_in[inc.j] == '1' && (*cmd)[inc.i].tab_fdin != NULL)
	{
		if (heredoc_prompting(cmd, inc, lastfd, envc) == 1)
			return (1);
	}
	else if ((*cmd)[inc.i].tab_fdin == NULL)
		return (1);
	return (0);
}

int	create_fdin(t_commands **cmd, t_inc inc, int *lastfd)
{
	if ((*cmd)[inc.i].flag_in[inc.j] == '0' && (*cmd)[inc.i].tab_fdin != NULL)
	{
		if (access((*cmd)[inc.i].tab_infile[inc.j], F_OK) == 0)
		{
			if (access((*cmd)[inc.i].tab_infile[inc.j], R_OK) == 0)
				*lastfd = open((*cmd)[inc.i].tab_infile[inc.j], O_RDONLY);
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
