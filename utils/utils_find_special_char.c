/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_special_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:33:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/22 19:27:25 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_special_char(char c, t_f_str f_str, t_inc *inc, char *s_c)
{
	int	i;

	if (inc->l_j == inc->j)
		i = inc->l_e;
	else
	{
//		if (inc->l_i != 0)
//			inc->k = inc->k - inc->l_e;
		inc->l_j = inc->j;
		i = 0;
	}
	while (f_str.sp_chars[inc->k] != '\0' && s_c[i] != '\0')
	{
		if (f_str.sp_chars[inc->k] == c && f_str.quotes[inc->k] == '0')
		{
				inc->l_i = i;
				return (i);
		}
		inc->k += 1;
		i++;
	}
	inc->l_i = 0;
	return (-1);
}
