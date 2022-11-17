/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tab_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:39:12 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/17 16:56:05 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strdup_n_to_i(char const *src, size_t n, size_t index, char **tab)
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

static void	count_redirections(t_commands *commands, t_flag_string f_str, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (tab[k] != 0)
	{
		j = 0;
		while (tab[k][j] != '\0')
		{
			if (f_str.special_chars[i] == '5' && f_str.quotes[i] == '0')
				i++;
			if (f_str.quotes[i] != '\0')
			{
				if (tab[k][j] == '>' && f_str.quotes[i] == '0')
					commands->nb_outfile += 1;
				if (tab[k][j] == '<' && f_str.quotes[i] == '0')
					commands->nb_infile += 1;
				i++;
			}
			j++;
		}
		k++;
	}
}
