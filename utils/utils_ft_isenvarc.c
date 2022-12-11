/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_isenvarc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:40:28 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/11 16:15:17 by fsariogl         ###   ########.fr       */
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
	else if (mode == 0)
	{
		if (c == '_' || ft_isalnum(c) != 0)
			return (1);
	}
	return (0);
}
