/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:49:40 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/28 16:03:21 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findc(char const *str, char const c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	char	*trim;

	if (!s1)
		return (NULL);
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	i = 0;
	while (ft_findc(set, s1[i]) == 1)
		i++;
	while (s1_len > i && (ft_findc(set, s1[s1_len - 1]) == 1))
		s1_len--;
	trim = malloc(sizeof(char) * (s1_len - i + 1));
	if (!trim)
		return (NULL);
	j = 0;
	while (i < s1_len)
		trim[j++] = s1[i++];
	trim[j] = '\0';
	return (trim);
}
