/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:06:58 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/17 11:33:42 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_free_all_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strdup_n_to_i(char const *src, size_t n, size_t index, char **tab)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * ((index - n) + 1));
	if (!dest)
	{
		ft_free_all_tab(tab);
		return (NULL);
	}
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

size_t	ft_nb_str(char const *str, char c)
{
	size_t	i;
	size_t	nb_str;
	size_t	stat;

	i = 0;
	nb_str = 0;
	stat = 1;
	if (c == 0)
	{
		nb_str++;
		return (nb_str);
	}
	while (str[i])
	{
		if (stat == 1 && str[i] && str[i] != c)
		{
			stat = 0;
			nb_str++;
		}
		if (str[i] && str[i] == c)
			stat = 1;
		i++;
	}
	return (nb_str);
}

void	ft_splitting(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	n;
	size_t	line;

	i = 0;
	n = 0;
	line = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i] && (line < ft_nb_str(s, c)))
	{
		n = i;
		while (s[i] && (s[i] != c))
			i++;
		tab[line++] = ft_strdup_n_to_i(s, n, i, tab);
		while (s[i] && (s[i] == c))
			i++;
	}
	tab[line] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_str(s, c) + 1));
	if (!tab)
		return (NULL);
	ft_splitting(tab, s, c);
	return (tab);
}
