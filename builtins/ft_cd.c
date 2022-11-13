/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:56:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/13 14:57:49 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **tab, int nb_comm)
{
	if (!tab[1])
		return (1);
	chdir(tab[1]);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
