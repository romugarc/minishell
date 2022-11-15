/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_in_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:41 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/15 17:43:29 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(t_flag_string flag_string, int i)
{
	if (flag_string.quotes[i] == '2' || flag_string.quotes[i] == '1')
		return (1);
	return (0);
}
