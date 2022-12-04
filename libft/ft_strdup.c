/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:15:48 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/04 14:11:26 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*dup;

	i = 0;
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	dup = malloc(sizeof(char) * (s1_len + 1));
	if (!dup)
		return (NULL);
	while (i <= s1_len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
