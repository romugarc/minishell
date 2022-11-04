/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/04 14:43:33 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int		i;
	pid_t	pid;
	int		fd[2];
	int		status;
	int		nb_commands;

	i = 0;
	nb_commands = nb_pipes;
	if (!commands)
		return (-1);
	while (nb_commands > 0)
	{
		if (nb_commands > 1)
		{
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			if (nb_commands != 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (nb_commands != nb_pipes)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
		i++;
		nb_commands--;
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (0);
}