/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/08 19:50:28 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(int **tab, int i)
{
	int	temp;

	temp = 0;
	while (temp < i)
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

int	**tab_fd_mall(int nb_comm)
{
	int	i;
	int **ret;
	
	ret = malloc(sizeof(int *) * (nb_comm + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nb_comm)
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


void	child_process(t_commands *commands, int temp, int nb_comm, t_exec exec)
{
	{
			if (temp != nb_comm && nb_comm > 1)
			{
				dup2(exec.fd[exec.comm_i - 1][0], 0);
				close_fd(exec.fd, exec.comm_i);
			}
			if (temp != 1)
			{
				dup2(exec.fd[exec.comm_i][1], 1);
				close_fd(exec.fd, exec.comm_i);
			}
			execve(commands[exec.comm_i].single_command[0], commands[exec.comm_i].single_command, exec.envp);
			printf("Errno >> %d\n", errno);
			perror(commands[exec.comm_i].single_command[0]);
			exit(EXIT_SUCCESS);
		}
}

int	pipe_error_case(int nb_comm, t_exec exec)
{
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i);
	free(exec.cpid);
	free_tab(exec.fd, exec.comm_i);
	return (1);
}

int	free_all(t_exec exec, int nb_comm)
{
	if (exec.cpid)
		free(exec.cpid);
	if (exec.fd)
		free_tab(exec.fd, nb_comm);
	return (1);
}

int	exec_init(t_exec *exec, t_commands *commands, int nb_comm, char **envp)
{
	(*exec).comm_i = 0;
	(*exec).status = 0;
	(*exec).envp = envp;
	(*exec).temp = nb_comm;
	(*exec).cpid = malloc(sizeof(int) * (nb_comm + 1));
	(*exec).fd = tab_fd_mall(nb_comm);
	if (!(*exec).cpid || !(*exec).fd)
		return (free_all((*exec), nb_comm));
	if (!commands)
		return (1);
	return (0);
}

int	exec_main(t_commands *commands, int nb_comm, char **envp)
{
	t_exec		exec;

	if (exec_init(&exec, commands, nb_comm, envp) == 1)
		return (1);
	while (exec.temp > 0)
	{
		if (exec.temp > 1)
			if (pipe(exec.fd[exec.comm_i]) == -1)
				return (pipe_error_case(nb_comm, exec));
		exec.cpid[exec.comm_i] = fork();
		if (exec.cpid[exec.comm_i] == 0)
			child_process(commands, exec.temp, nb_comm, exec);
		exec.comm_i++;
		exec.temp--;
	}
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i);
	wait_all_cpid(exec.cpid, exec.status, exec.comm_i - 1);
	free_all(exec, nb_comm);
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
