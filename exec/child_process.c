/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:57:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/10 15:26:55 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_commands *cmd, t_exec exec, t_envlist **envc, int *oldp_stat)
{
	dup_fd(exec, exec.nb_comm, cmd);
	if (is_it_builtin(cmd[exec.comm_i].sgl_cmd[0]) == 1)
	{
		is_builtins(cmd[exec.comm_i], exec, envc, oldp_stat);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmd[exec.comm_i].sgl_cmd[0],
			cmd[exec.comm_i].sgl_cmd, exec.env_tmp);
		//gestion erreur command not found a la place de perror a mettre ici
		perror(cmd[exec.comm_i].sgl_cmd[0]);
		exit(127);
	}
}
