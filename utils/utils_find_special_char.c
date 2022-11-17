/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_special_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:33:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/17 17:04:36 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static	void	reset_k(t_flag_string f_str, t_inc *inc)
{
	int	i;

	i = 0;
	while (inc->k >= 0 && i == 0)
	{
		if (f_str.special_chars[inc->k] == '9' && f_str.quotes[inc->k] == 0)
			i = 1;
		else
			inc->k -= 1;
	}
}*/

int	find_special_char(char c, t_flag_string f_str, t_inc *inc, char *s_c)
{
	int	i;

	printf("%d\t%djj\n", inc->j, inc->l_j);
	if (inc->l_j == inc->j)
		i = inc->l_e;
	else
	{
		//reset_k(f_str, inc);
		printf("%d\t%die\n", inc->l_i, inc->l_e);
		if (inc->l_i != 0)
			inc->k = inc->k - inc->l_e;
		printf("%dk\n", inc->k);
		inc->l_j = inc->j;
		i = 0;
	}
	while (f_str.special_chars[inc->k] != '\0' && s_c[i] != '\0')
	{
		printf("%c\t%c\n", f_str.special_chars[inc->k], s_c[i]);
		if (f_str.special_chars[inc->k] == c && f_str.quotes[inc->k] == '0')
		{
			if (f_str.special_chars[inc->k + 1] != c)
			{
				inc->l_i = i;
				return (i);
			}
		}
		inc->k += 1;
		i++;
	}
	inc->l_i = 0;
	return (-1);
}
