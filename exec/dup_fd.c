/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:18:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/23 16:03:42 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_fd(t_exec exec, int nb_comm)
{
	if (exec.temp != nb_comm && nb_comm > 1)
	{
		dup2(exec.fd[exec.comm_i - 1][0], 0);
		close_fd(exec.fd, exec.comm_i - 1);
	}
	if (exec.temp != 1)
	{
		dup2(exec.fd[exec.comm_i][1], 1);
		close_fd(exec.fd, exec.comm_i);
	}
}
