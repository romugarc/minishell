/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/02 19:23:57 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int		i;
	int		ret;
	pid_t	pid;
	int		fd[2];

	i = 0;
	if (!commands)
		return (-1);
	while (nb_pipes > 0)
	{
		if (nb_pipes > 1)
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		printf("%d\n", fd[0]);
		printf("%d\n", fd[1]);
		pid = fork();
		if (pid == 0)
		{
			if (nb_pipes > 1)
				dup2(fd[1], 1);
			printf("Fils = %d\n", nb_pipes);
			close(fd[0]);
			close(fd[1]);
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Parent = %d\n", nb_pipes);
			waitpid(pid, &ret, 0);
			if (ret != 0)
				exit(EXIT_FAILURE);
			close(fd[0]);
			close(fd[1]);
			if (nb_pipes > 1)
				dup2(fd[0], 0);
		}
		nb_pipes--;
		i++;
	}
	return (0);
}