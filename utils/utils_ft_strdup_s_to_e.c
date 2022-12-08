/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_strdup_s_to_e.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:19:26 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/08 15:19:58 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_s_to_e(char const *src, size_t n, size_t index)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * ((index - n) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[n] && n < index)
	{
		dest[i] = src[n];
		n++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
