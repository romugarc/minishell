/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_malloc_tab_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/21 19:01:32 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	malloc_chain_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].flag_in = malloc(sizeof(char) * (*c)[i].nb_infile + 1);
			if (!(*c)[i].tab_infile)
				return (1);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].flag_out = malloc(sizeof(char) * (*c)[i].nb_outfile + 1);
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	return (0);
}

int	malloc_tab_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].tab_infile = malloc(sizeof(char *) * ((*c)[i].nb_infile + 1));
			if (!(*c)[i].tab_infile)
				return (1);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * ((*c)[i].nb_outfile + 1));
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	if (malloc_chain_files(c, nb_pipes) == 1)
		return (1);
	return (0);
}
