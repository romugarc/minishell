/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_increment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:55:25 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/19 15:08:54 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_increment(char const *s, char c, size_t *i, t_f_str f_str)
{
	while (s[*i])
	{
		if (s[*i] == c && is_in_quotes(f_str, (f_str.i.l_i + *i)) != 0)
			*i = *i + 1;
		else if (s[*i] != c)
			*i = *i + 1;
		else
			break ;
	}
}
