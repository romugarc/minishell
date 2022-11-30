/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_fd_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:13:21 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/30 18:25:07 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

static int	heredoc_prompting(t_commands **cmd, int i, int j, int *lastfd)
{
	int	*pipefd;
	int	cpid;
	int	status;
	char	*lineh;

	pipefd = malloc(sizeof(int) * 2);
	lineh = NULL;
	if (pipe(*pipefd) == -1)
		return (1);
	*cpid = fork();
	if (*cpid == -1)
	{
		close(*pipefd[0]);
		close(*pipefd[1]);
		free(*pipefd);
		return (1);
	}
	else if (cpid == 0)
	{
		close(pipefd[1]);
		while (1)
		{
			lineh = readline("> ");
			if (ft_strrcmp(lineh, (*cmd)[i].tab_infile[j]) == 0)
			{
				//leaks dans le heredoc (qui viennent de ce child)
				free(lineh);
				break;
			}
			free(lineh);
		}
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[0]);
		*lastfd = pipefd[1];
		(*cmd)[i].tab_fdin[j] = *lastfd;
		waitpid(cpid, &status, 0);
		(*cmd)[i].heredoc = 1;
		free(pipefd);
	}
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

int	create_fdinnnnn(t_commands **cmd, int i, int j, int *lastfd)
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
