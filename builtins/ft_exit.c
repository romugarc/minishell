/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:42:20 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/14 11:13:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **cmd, int nb_comm)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i <= 2)
	{
		if (cmd[1])
		{
			i = 0;
			while (cmd[1][i])
			{
				if (ft_isdigit(cmd[1][i]) == 0)
				{
					printf("exit\n");
					ft_putstr_fd("minishell: exit: ", 2);
					ft_putstr_fd(cmd[1], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
					exit(255);
				}
				i++;
			}
			printf("exit\n");
			if (cmd[1])
				exit(ft_atoi(cmd[1]) % 256);
			else
				exit(EXIT_SUCCESS);
		}
		if (nb_comm == 1)
			printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	printf("exit\n");
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	g_errno = 1;
}