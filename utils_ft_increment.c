/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_increment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:55:25 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/31 16:55:44 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increment(char const *s, char c, size_t *i, t_flag_string f_str)
{
	while (s[*i])
	{
		if (s[*i] == c && is_in_quotes(f_str, *i) != 0)
			*i = *i + 1;
		else if (s[*i] != c)
			*i = *i + 1;
		else
			break ;
	}
}
