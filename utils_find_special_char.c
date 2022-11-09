/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_special_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:33:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/07 19:34:45 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_special_char(char c, t_flag_string f_str, int *k)
{
	while (f_str.special_chars[*k] != '\0')
	{
		if (f_str.special_chars[*k] == c && f_str.quotes[*k] == '0')
		{
			if (f_str.special_chars[*k + 1] != c)
				return (*k);
		}
		*k += 1;
	}
	return (*k);
}
