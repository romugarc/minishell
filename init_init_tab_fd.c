/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init_tab_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:07:56 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 17:21:54 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_tab_fd(int nb_file)
{
	int	i;
	int	*tab_fd;

	tab_fd = malloc(sizeof(int) * nb_file);
	if (!tab_fd)
		return (NULL);
	i = 0;
	if (nb_file > 0)
	{
		while (i < nb_file)
		{
			tab_fd[i] = -1;
			i++;
		}
	}
	else
		tab_fd = NULL;
	return (tab_fd);
}
