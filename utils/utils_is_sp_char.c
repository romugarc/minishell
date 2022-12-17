/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_sp_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:57:08 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 11:57:44 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_sp_char(t_f_str f_str, int i)
{
	if (f_str.sp_chars[i] >= '3' && f_str.sp_chars[i] <= '9' \
		&& f_str.quotes[i] == '0')
		return (f_str.sp_chars[i] - '0');
	return (0);
}
