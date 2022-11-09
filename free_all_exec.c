/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:59:11 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/09 13:00:17 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(int **tab, int i)
{
	int	temp;

	temp = 0;
	while (temp < i)
	{
		free(tab[temp]);
		temp++;
	}
	free(tab);
}

int	free_all(t_exec exec, int nb_comm)
{
	if (exec.cpid)
		free(exec.cpid);
	if (exec.fd)
		free_tab(exec.fd, nb_comm);
	return (1);
}
