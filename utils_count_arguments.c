/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_count_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:35:11 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/28 18:33:33 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(char *line, char c)
{
	int		count;
	int		i;
	int		flag_count;
	int		last_quote;

	count = 0;
	flag_count = 1;
	last_quote = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (flag_count == 1 && line[i] != c && line[i] != '\n')
		{
			flag_count = 0;
			count++;
		}
		if (line[i] == c && line[i] != '\0')
			flag_count = 1;
		i++;
	}
	return (count);
}
