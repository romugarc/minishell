/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:13:21 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/06 17:11:24 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_routine(t_commands **cmd, t_inc inc, t_heredoc *hd)
{
	int		breaking;
	char	*lineh;

	breaking = 0;
	lineh = NULL;
	lineh = readline("> ");
	if (ft_strrcmp(lineh, (*cmd)[inc.i].tab_infile[inc.j]) == 0)
	{
		free(lineh);
		breaking = 1;
	}
	else
	{
		ft_putstr_fd(lineh, hd->pipefd[1]);
		ft_putchar_fd('\n', hd->pipefd[1]);
		free(lineh);
	}
	return (breaking);
}

static int	heredoc_prompting(t_commands **cmd, int i, int j, int *lastfd)
{
	t_heredoc hd;
	t_inc	inc;
	int		fdsave;

	inc.i = i;
	inc.j = j;
	fdsave = dup(0);
	hd.pipefd = malloc(sizeof(int) * 2);
	if (pipe(hd.pipefd) == -1)
		return (1);
	while (1)
	{
		if(heredoc_routine(cmd, inc, &hd) == 1)
			break;
	}
	dup2(hd.pipefd[1], fdsave);
	close(hd.pipefd[1]);
	close(fdsave);
	*lastfd = hd.pipefd[0];
	(*cmd)[inc.i].tab_fdin[inc.j] = *lastfd;
	(*cmd)[inc.i].heredoc = 1;
	free(hd.pipefd);
	return (0);
}

static int	create_fdin2(t_commands **cmd, int i, int j, int *lastfd)
{
	if ((*cmd)[i].flag_in[j] == '1' && (*cmd)[i].tab_fdin != NULL)
	{
		if (heredoc_prompting(cmd, i, j, lastfd) == 1)
			return (1);
	}
	else if ((*cmd)[i].tab_fdin == NULL)
		return (1);
	return (0);
}

int	create_fdin(t_commands **cmd, int i, int j, int *lastfd)
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
		(*cmd)[i].tab_fdin[j] = *lastfd;
	}
	else
	{
		if(create_fdin2(cmd, i, j, lastfd) == 1)
			return (1);
	}
	return (0);
}
