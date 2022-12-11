/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_isenvarc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:40:28 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/11 12:39:36 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isenvarc(char c, int mode)
{
	if (mode == 1)
	{
		if (c == '_' || ft_isalpha(c) != 0)
			return (1);
	}
	if (mode == 0)
	{
		if (c == '_' || ft_isalnum(c) != 0)
			return (1);
	}
	return (0);
}
