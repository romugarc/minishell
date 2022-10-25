/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:10:46 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/26 16:21:18 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		s_len;

	s_len = 0;
	while (s[s_len])
		s_len++;
	i = 0;
	while (i <= s_len)
	{
		if (s[s_len - i] == (c % 256))
			return ((char *)&s[s_len - i]);
		i++;
	}
	return (NULL);
}
