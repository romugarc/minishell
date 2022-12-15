/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:42:20 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/15 16:08:26 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **cmd, int nb_comm)
{
	int	i;
	int	caractere;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 2)
	{
		caractere = 0;
		while (cmd[1][caractere])
		{
			if (ft_isdigit(cmd[1][caractere]) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			caractere++;
		}
		if (i <= 2)
		{
			ft_putstr_fd("exit\n", 2);	
			exit(ft_atoi(cmd[1]) % 256);
		}
	}
	if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_errno = 1;
		return ;
	}
	if (nb_comm == 1)
		ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}