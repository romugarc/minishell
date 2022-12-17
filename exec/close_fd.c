/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:00:51 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/06 13:51:40 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int **fd, int i, t_cmd *cmd)
{
	while (i >= 0)
	{
		if (fd[i][0] > 2)
			close(fd[i][0]);
		if (fd[i][1] > 2)
			close(fd[i][1]);
		if (cmd[i].fdin >= 3)
			close(cmd[i].fdin);
		if (cmd[i].fdout >= 3)
			close(cmd[i].fdout);
		i--;
	}
}
