/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/02 15:04:32 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_main(t_commands *commands, int nb_pipes, char **envp)
{
	int		i;
	int		ret;
	pid_t	pid;
	int		fd[2];
	int		t1;
	int		t2 = 0;

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
			close(fd[0]);
			close(fd[1]);
			t1 = dup(t2);
			printf("t1 = %d\nt2 = %d", t1, t2);
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &ret, 0);
			if (ret != 0)
				exit(EXIT_FAILURE);
			close(fd[0]);
			close(fd[1]);
		}
		nb_pipes--;
		i++;
	}
}