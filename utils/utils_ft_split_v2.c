/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_split_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:06:58 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 16:47:02 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_all_tab(char **tab)
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

static char	*ft_strdup_n_to_i(char *src, size_t n, size_t index, char **tab)
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

static size_t	ft_nb_str(char *str, char c, t_f_str *f_str)
{
	size_t	i;
	size_t	nb_str;
	size_t	stat;

	f_str->i.l_i = f_str->i.i;
	i = 0;
	nb_str = 0;
	stat = 1;
	if (c == 0)
		nb_str++;
	while (str[i] && c != 0)
	{
		if (stat == 1 && str[i] && str[i] != c)
		{
			stat = 0;
			nb_str++;
		}
		if (str[i] && str[i] == c && is_in_quotes(*f_str, f_str->i.i) == 0)
			stat = 1;
		f_str->i.i += 1;
		i++;
	}
	return (nb_str);
}

static void	ft_splitting(char **tab, char *s, char c, t_f_str *f_str)
{
	size_t	i;
	size_t	n;
	size_t	line;
	size_t	nb_str;

	i = 0;
	n = 0;
	line = 0;
	nb_str = ft_nb_str(s, c, f_str);
	while (s[i] && (s[i] == c))
		i++;
	while (s[i] && (line < nb_str))
	{
		n = i;
		ft_increment(s, c, &i, *f_str);
		tab[line++] = ft_strdup_n_to_i(s, n, i, tab);
		while (s[i] && (s[i] == c))
			i++;
	}
	tab[line] = 0;
}

char	**ft_split_v2(char *s, char c, t_f_str *f_str)
{
	char	**tab;
	int		size;

	if (!s)
		return (NULL);
	size = count_arguments(s, c, f_str);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	ft_splitting(tab, s, c, f_str);
	return (tab);
}
