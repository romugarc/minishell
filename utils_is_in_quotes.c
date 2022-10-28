/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_in_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:38:55 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/28 18:28:59 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(char	*str, int index, int *last_quote)
{
	int	i;
	int	j;

	i = *last_quote;
	printf("%c\n", str[index]);
	while (str[i] != '"' && str[i] != 39 && str[i] != '\0')
		i++;
	printf("%c\n", str[i]);
	if (str[i] != '\0')
		j = i + 1;
	else
		return (0);
	while (str[j] != '"' && str[i] != 39 && str[j] != '\0')
		j++;
	if (str[j] != '\0')
		*last_quote = j;
	else
		*last_quote = i;
	if (index > i && str[i] != '\0' && index < j && str[j] != '\0')
		return (1);
	return (0);
}
