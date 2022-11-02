/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/02 17:12:46 by fsariogl         ###   ########.fr       */
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
		return ;
	while (nb_pipes > 0)
	{
		if (nb_pipes > 1)
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
		pid = fork();
		if (pid == 0)
		{
			printf("\ntesttt\n");
			execve(commands[i].single_command[0], commands[i].single_command, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &ret, 0);
			if (ret != 0)
				exit(EXIT_FAILURE);
			dup2(1, 0);
		}
		nb_pipes--;
		i++;
	}
}