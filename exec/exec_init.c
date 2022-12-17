/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:01:41 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 16:11:13 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**tab_fd_mall(int nb_comm)
{
	int	i;
	int	**ret;

	ret = malloc(sizeof(int *) * (nb_comm + 1));
	if (!ret)
	{
		g_errno = 134;
		return (NULL);
	}
	i = 0;
	while (i < nb_comm)
	{
		ret[i] = malloc(sizeof(int) * 2);
		if (!ret[i])
		{
			free_tab(ret, i);
			g_errno = 134;
			return (NULL);
		}
		i++;
	}
	return (ret);
}

int	exec_init(t_exec *exec)
{
	(*exec).comm_i = 0;
	(*exec).status = 0;
	(*exec).nb_comm = (*exec).temp;
	(*exec).error = 0;
	(*exec).cpid = malloc(sizeof(int) * ((*exec).temp));
	(*exec).fd = tab_fd_mall((*exec).temp);
	if (!(*exec).cpid || !(*exec).fd)
	{
		g_errno = 134;
		return (free_all((*exec), (*exec).temp));
	}
	return (0);
}
