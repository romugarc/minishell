/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:01:41 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/09 13:02:21 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**tab_fd_mall(int nb_comm)
{
	int	i;
	int	**ret;

	ret = malloc(sizeof(int *) * (nb_comm + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nb_comm)
	{
		ret[i] = malloc(sizeof(int) * 2);
		if (!ret[i])
		{
			free_tab(ret, i);
			return (NULL);
		}
		i++;
	}
	return (ret);
}

int	exec_init(t_exec *exec, t_commands *commands, int nb_comm, char **envp)
{
	(*exec).comm_i = 0;
	(*exec).status = 0;
	(*exec).envp = envp;
	(*exec).temp = nb_comm;
	(*exec).cpid = malloc(sizeof(int) * (nb_comm + 1));
	(*exec).fd = tab_fd_mall(nb_comm);
	if (!(*exec).cpid || !(*exec).fd)
		return (free_all((*exec), nb_comm));
	if (!commands)
		return (1);
	return (0);
}
