/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:01:01 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 19:19:20 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (++i < s1_len)
		str[i] = s1[i];
	i = -1;
	while (++i <= s2_len)
		str[i + s1_len] = s2[i];
	return (str);
}
