/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:00:51 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/09 13:01:02 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int **fd, int i)
{
	i = i - 1;
	while (i >= 0)
	{
		if (fd[i][0] > 2 && fd[i][1] > 2)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		i--;
	}
}