/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:31:07 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:39:55 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	remove_quotes_intab(t_cmd **cmd, int i)
{
	int		j;

	if ((*cmd)[i].nb_inf > 0)
	{
		j = 0;
		while ((*cmd)[i].tab_inf[j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i].tab_inf[j]) == 1)
				return (1);
			j++;
		}
	}
	if ((*cmd)[i].nb_outf > 0)
	{
		j = 0;
		while ((*cmd)[i].tab_outf[j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i].tab_outf[j]) == 1)
				return (1);
			j++;
		}
	}
	return (0);
}

int	remove_quotes(t_cmd **cmd, int np)
{
	t_inc	i;

	init_inc(&i);
	while (i.i < np)
	{
		i.j = 0;
		while ((*cmd)[i.i].sgl_cmd[i.j] != NULL)
		{
			if (removing_quotes(&(*cmd)[i.i].sgl_cmd[i.j]) == 1)
				return (1);
			i.j++;
		}
		if (remove_quotes_intab(cmd, i.i) == 1)
			return (1);
		i.i++;
	}
	return (0);
}
