/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_id_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:10:40 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:11:13 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_id_exp_1(char *var, char *cmd, int *i)
{
	*i = 0;
	while (var[*i] && var[*i] != '=' && var[*i] != '+')
	{
		if (ft_isenvarc(var[0], 1) == 0 || ft_isenvarc(var[*i], 0) == 0)
			return (puterror(cmd, var, 3, 0));
		*i += 1;
	}
	return (0);
}

int	valid_id_exp(char *var, char *cmd, int *oldp_stat)
{
	int	i;

	if (valid_id_exp_1(var, cmd, &i) == -1)
		return (-1);
	if (var[0] == '\0' || var[0] == '+' || var[0] == '=')
		return (puterror(cmd, var, 3, 0));
	if (var[i] == '+')
	{
		if (var[i + 1] == '=')
		{
			if (strcmp_tof(var, "PWD") == 1)
				(*oldp_stat) = 0;
			return (2);
		}
		else
			return (puterror(cmd, var, 3, 0));
	}
	if (strcmp_tof(var, "PWD") == 1)
		(*oldp_stat) = 0;
	return (1);
}
