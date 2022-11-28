/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_form_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:08:18 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 19:32:40 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	form_heredoc(t_commands **c, int nb_pipes)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			j = 0;
			while ((*c)[i].tab_fdin[j] != '\0')
			{
				if ((*c)[i].tab_fdin[j] == '1')
					(*c)[i].nb_hd += 1;
				j++;
			}
			if ((*c)[i].nb_hd > 0)
			{
				(*c)[i].tab_hd = malloc(sizeof(char *) * ((*c)[i].nb_hd + 1));
				if (!(*c)[i].tab_hd)
					return (1);
				j = 0;
				k = 0;
				while ((*c)[i].tab_fdin[j] != '\0')
				{
					if ((*c)[i].tab_fdin[j] == '1')
					{
						(*c)[i].tab_hd[k] = ft_strdup((*c)[i].tab_infile[j]);
						k++;
					}
					j++;
				}
			}
		}
		i++;
	}
	return (0);
}
//gerer les free et malloc correctement en faisant nb_infile - nb_heredoc dans malloc_tab_files (y aura ptet un souci la, regarder si c'est pas mieux de malloc apres reform tab)
