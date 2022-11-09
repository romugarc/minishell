/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:57:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/09 13:06:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		execve(commands[exec.comm_i].single_command[0],
			commands[exec.comm_i].single_command, exec.envp);
		perror(commands[exec.comm_i].single_command[0]);
		exit(EXIT_SUCCESS);
	}
}
