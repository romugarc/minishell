/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_special_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:33:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 11:47:40 by rgarcia          ###   ########lyon.fr   */
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
		inc->l_j = inc->j;
		i = 0;
		inc->k = 0;
	}
	while (f_str.sp_chars[inc->k] != '\0' && s_c[i] != '\0')
	{
		if (f_str.sp_chars[inc->k] == c && f_str.quotes[inc->k] == '0')
			return (i);
		inc->k += 1;
		i++;
	}
	return (-1);
}
