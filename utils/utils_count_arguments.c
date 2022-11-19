/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_count_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:35:11 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/19 15:08:30 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arguments(char *line, char c, t_f_str *f_str)
{
	int		count;
	int		i;
	int		flag_count;

	count = 0;
	flag_count = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (flag_count == 1 && line[i] != c && line[i] != '\n')
		{
			flag_count = 0;
			count++;
		}
		if (line[i] == c && line[i] != '\0' \
			&& is_in_quotes(*f_str, f_str->i.k) == 0)
			flag_count = 1;
		f_str->i.k += 1;
		i++;
	}
	return (count);
}
