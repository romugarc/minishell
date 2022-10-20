/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:09:42 by rgarcia           #+#    #+#             */
/*   Updated: 2022/02/25 10:10:41 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_to_i(char *s1, char *s2, int max_len)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*str;

	i = -1;
	s1_len = 0;
	s2_len = 0;
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2 && s2[s2_len] && (s2_len <= max_len))
		s2_len++;
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (s1 && (++i < s1_len))
		str[i] = s1[i];
		i = -1;
	while (s2 && (++i < s2_len))
	{
		str[i + s1_len] = s2[i];
	}
	str[i + s1_len] = '\0';
	free(s1);
	return (str);
}
