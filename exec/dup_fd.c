/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:18:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/07 20:27:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_fd(t_exec exec, int nb_comm, t_cmd *cmd)
{
	if (cmd[exec.comm_i].fdin >= 3)
		dup2(cmd[exec.comm_i].fdin, 0);
	else if (exec.temp != nb_comm && nb_comm > 1)
		dup2(exec.fd[exec.comm_i - 1][0], 0);
	close_fd(exec.fd, exec.comm_i - 1, cmd);
	if (cmd[exec.comm_i].fdout >= 3)
		dup2(cmd[exec.comm_i].fdout, 1);
	else if (exec.temp != 1)
		dup2(exec.fd[exec.comm_i][1], 1);
	close_fd(exec.fd, exec.comm_i, cmd);
}
