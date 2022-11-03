/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/03 19:31:38 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int		i;
//	int		io;
//	int		ret;
	int		pid;
	int		pid2;
	int		fd[2];
	int		nb_commands;

	i = 0;
	nb_commands = (nb_pipes * 2) - 1;
	if (!commands)
		return (-1);
	printf("%s\n", commands[1].single_command[0]);
//	while (nb_commands > 0)
//	{
//		io = nb_commands % 2;
//		if (nb_commands > 1)
//		{
		if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
//		}
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
//			perror("CHLD ");
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
//		printf("test 22 >> fd0 = %d >>>> fd1 = %d\n", fd[0], fd[1]);
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
//			perror("CHLD ");
			//printf("%s\n", commands[i].single_command[0]);
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
//		waitpid(pid, NULL, 0);
//		waitpid(pid2, NULL, 0);
//		if (ret != 0)
//			exit(EXIT_FAILURE);
//		perror("PAR ");
//		nb_commands--;
//		i++;
//	}
		close(fd[1]);
		close(fd[0]);
	return (0);
}