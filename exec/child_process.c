/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:57:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/19 16:47:20 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_commands *commands, t_exec exec, int nb_comm)
{
	dup_fd(exec, nb_comm);
	if (is_it_builtin(commands[exec.comm_i].sgl_cmd[0]) == 1)
		is_builtins(commands[exec.comm_i].sgl_cmd, nb_comm);
	else
	{
		execve(commands[exec.comm_i].sgl_cmd[0],
			commands[exec.comm_i].sgl_cmd, exec.envp);
		perror(commands[exec.comm_i].sgl_cmd[0]);
		exit(EXIT_SUCCESS);
	}
}
