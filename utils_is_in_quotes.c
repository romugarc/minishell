/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_in_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:38:55 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/26 16:43:28 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(char	*str, int index)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '"' && str[i] != 39 && str[i] != '\0')
		i++;
	j = 0;
	while (str[j] != '"' && str[i] != 39 && str[j] != '\0')
		j++;
	if (index > i && str[i] != '\0' && index < j && str[j] != '\0')
		return (1);
	return (0);
}
