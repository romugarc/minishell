/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:42:20 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/27 18:09:31 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **cmd, int nb_comm)
{
	if (cmd[1])
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
		exit(EXIT_FAILURE);
	}
	if (nb_comm == 1)
		printf("exit\n");
	exit(EXIT_SUCCESS);
}