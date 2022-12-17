/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:42:20 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 11:04:42 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_behaviour(char **cmd, int i, int flag_exit)
{
	if (i == 2 && flag_exit == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(cmd[1]) % 256);
	}
	else if (flag_exit == 1)
		exit(255);
	else if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_errno = 1;
		return (-1);
	}
	return (0);
}

void	ft_exit(char **cmd, int nb_comm)
{
	int	i;
	int	flag_exit;
	int	caractere;

	i = 0;
	while (cmd[i])
		i++;
	if (i >= 2)
	{
		caractere = 0;
		while (cmd[1][caractere])
		{
			if (ft_isdigit(cmd[1][caractere]) == 0)
			{
				puterror(cmd[1], NULL, 6, 0);
				flag_exit = 1;
			}
			caractere++;
		}
		if (exit_behaviour(cmd, i, flag_exit) == -1)
			return ;
	}
	if (nb_comm == 1)
		ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
