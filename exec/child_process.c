/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:57:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/27 12:55:08 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_commands *cmd, t_exec exec, int nb_comm, t_envlist **envc)
{
	dup_fd(exec, nb_comm);
	if (is_it_builtin(cmd[exec.comm_i].sgl_cmd[0]) == 1)
		is_builtins(cmd[exec.comm_i].sgl_cmd, nb_comm, envc);
	else
	{
		execve(cmd[exec.comm_i].sgl_cmd[0],
			cmd[exec.comm_i].sgl_cmd, exec.env_tmp);
		perror(cmd[exec.comm_i].sgl_cmd[0]);
		exit(EXIT_SUCCESS);
	}
}
