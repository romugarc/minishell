/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_close_tab_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:54 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/06 19:01:53 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_tab_fd(int *tab_fd, int nb_file)
{
	int	i;

	i = 0;
	if (tab_fd != NULL)
	{
		while (i < nb_file)
		{
			if (tab_fd[i] >= 3)
				close(tab_fd[i]);
			i++;
		}
	}
}
