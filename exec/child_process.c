/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:57:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 19:02:37 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_commands *cmd, t_exec *exec, t_envlist **envc, int *oldp)
{
	if (cmd[(*exec).comm_i].sgl_cmd == NULL)
		exit(EXIT_SUCCESS);
	else if (cmd[(*exec).comm_i].sgl_cmd[0] == NULL)
		exit(EXIT_SUCCESS);
	dup_fd((*exec), (*exec).nb_comm, cmd);
	if (check_cmd_fd(cmd[(*exec).comm_i]) == -1)
		exit(1);
	else if (check_access(cmd[(*exec).comm_i], envc) == -1)
		exit(127);
	else if (is_it_builtin(cmd[(*exec).comm_i].sgl_cmd[0], exec) == 1)
	{
		is_builtins(cmd[(*exec).comm_i], exec, envc, oldp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmd[(*exec).comm_i].sgl_cmd[0],
			cmd[(*exec).comm_i].sgl_cmd, (*exec).env_tmp);
		perror(cmd[(*exec).comm_i].sgl_cmd[0]);
		exit(127);
	}
}
