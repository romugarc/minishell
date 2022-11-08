/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/08 14:41:06 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(int **tab, int i)
{
	int	temp;

	temp = 0;
	while (temp != i)
	{
		free(tab[temp]);
		temp++;
	}
	free(tab);
}

void	close_fd(int **fd, int i)
{
	i = i - 1;
	while (i >= 0)
	{
		if (fd[i][0] > 2 && fd[i][1] > 2)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		i--;
	}
}

void	wait_all_cpid(pid_t *cpid, int status, int i)
{
	int	temp;

	temp = 0;
	status = 0;
	while (temp <= i)
	{
		waitpid(cpid[temp], &status, 0);
		temp++;
	}
}

int	**tab_fd_mall(int nb_pipes)
{
	int	i;
	int **ret;
	
	ret = malloc(sizeof(int *) * (nb_pipes + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		ret[i] = malloc(sizeof(int) * 2);
		if (!ret[i])
		{
			free_tab(ret, i);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

int	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int			i;
	pid_t		*cpid;
	int			**fd;
	int			status;
	int			nb_commands;

	i = 0;
	status = 0;
	cpid = malloc(sizeof(int) * (nb_pipes + 1));
	if (!cpid)
		return (1);
	fd = tab_fd_mall(nb_pipes);
	if (!fd)
	{
		free(cpid);
		return (1);
	}
	nb_commands = nb_pipes;
	if (!commands)
		return (1);
	while (nb_commands > 0)
	{
		if (nb_commands > 1)
		{
			if (pipe(fd[i]) == -1)
			{
				if (nb_pipes > 1)
					close_fd(fd, i);
				free(cpid);
				free_tab(fd, i);
				return (1);
			}
		}
		cpid[i] = fork();
		if (cpid[i] == 0)
		{
			if (nb_commands != nb_pipes && nb_pipes > 1)
			{
				dup2(fd[i - 1][0], 0);
				close_fd(fd, i);
			}
			if (nb_commands != 1)
			{
				dup2(fd[i][1], 1);
				close_fd(fd, i);
			}
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			printf("Errno >> %d\n", errno);
			perror(commands[i].single_command[0]);
			exit(EXIT_SUCCESS);
		}
		i++;
		nb_commands--;
	}
	if (nb_pipes > 1)
		close_fd(fd, i);
	wait_all_cpid(cpid, status, i - 1);
	free_tab(fd, i);
	free(cpid);
	return (0);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//	int	exec_main(t_commands *commands, int nb_pipes, char **envp)
//	{
//		int		i;
//		pid_t	cpid;
//		int		fd[3][2];
//		int		status;
//		int		nb_commands;
//	
//		i = 0;
//		nb_commands = nb_pipes;
//		if (!commands)
//			return (-1);
//		if (pipe(fd[0]) == -1)
//		{
//			printf(">>>>Pipe error<<<<<");
//			exit(EXIT_FAILURE);
//		}
//		
//	
//		cpid = fork();
//		if (cpid == 0)
//		{
//			dup2(fd[0][1], 1);
//			close(fd[0][0]);
//			close(fd[0][1]);
//			execve(commands[0].single_command[0], commands[0].single_command, envp);
//			exit(EXIT_SUCCESS);
//		}
//		
//		if (pipe(fd[1]) == -1)
//		{
//			printf(">>>>Pipe error<<<<<");
//			exit(EXIT_FAILURE);
//		}
//		
//		cpid = fork();
//		if (cpid == 0)
//		{
//			dup2(fd[0][0], 0);
//			dup2(fd[1][1], 1);
//			close(fd[1][0]);
//			close(fd[1][1]);
//			close(fd[0][0]);
//			close(fd[0][1]);
//			execve(commands[1].single_command[0], commands[1].single_command, envp);
//			exit(EXIT_SUCCESS);
//		}
//	
//	
//		cpid = fork();
//		if (cpid == 0)
//		{
//			dup2(fd[1][0], 0);
//			close(fd[2][0]);
//			close(fd[2][1]);
//			close(fd[1][0]);
//			close(fd[1][1]);
//			close(fd[0][0]);
//			close(fd[0][1]);
//			execve(commands[2].single_command[0], commands[2].single_command, envp);
//			exit(EXIT_SUCCESS);
//		}
//		
//		
//		close(fd[0][0]);
//		close(fd[0][1]);
//		close(fd[1][0]);
//		close(fd[1][1]);
//		close(fd[2][0]);
//		close(fd[2][1]);
//		waitpid(cpid, &status, 0);
//		return (0);
//	}
