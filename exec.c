/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/10/31 19:29:05 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int		i;
	int		ret;
	pid_t	pid;
	int		fd[2];

	i = 0;
	if (!commands)
		return ;
	while (nb_pipes > 0)
	{
		if (nb_pipes > 1)
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
		{
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			close(fd[0]);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &ret, 0);
			if (ret != 0)
				exit(EXIT_FAILURE);
			if (nb_pipes == 1)
				close(fd[0]);
			close(fd[1]);
			if (nb_pipes > 1)
				dup2(1, 0);
		}
		nb_pipes--;
		i++;
	}
}