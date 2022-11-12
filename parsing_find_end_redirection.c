/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_find_end_redirection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:51 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/09 16:09:41 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end_redirection(t_flag_string f_str, int *k)
{
	while (f_str.special_chars[*k] < '5' && f_str.special_chars[*k] != '\0')
		*k += 1;
	return (*k);
}
