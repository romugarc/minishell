/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:10:04 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	expand_var_tab2(t_cmd **cmd, t_envlist *envc, t_inc i)
{
	if ((*cmd)[i.i].nb_outf > 0)
	{
		i.l_i = 0;
		i.j = 0;
		while ((*cmd)[i.i].tab_outf[i.j] != NULL)
		{
			if (search_expand(&(*cmd)[i.i].tab_outf[i.j], envc) == 1)
				return (1);
			i.j++;
		}
	}
	return (0);
}

static int	expand_var_tab(t_cmd **cmd, t_envlist *envc, t_inc i)
{
	if ((*cmd)[i.i].nb_inf > 0)
	{
		i.l_i = 0;
		i.j = 0;
		while ((*cmd)[i.i].tab_inf[i.j] != NULL)
		{
			if ((*cmd)[i.i].flag_in[i.j] == '0')
			{
				if (search_expand(&(*cmd)[i.i].tab_inf[i.j], envc) == 1)
					return (1);
				i.j++;
			}
			else
				i.j++;
		}
	}
	if (expand_var_tab2(cmd, envc, i) == 1)
		return (1);
	return (0);
}

int	expand_variable(t_cmd **c, int np, t_envlist *envc)
{
	t_inc	i;

	init_inc(&i);
	while (i.i < np)
	{
		i.l_i = 0;
		i.j = 0;
		while ((*c)[i.i].sgl_cmd[i.j] != NULL)
		{
			if (search_expand(&(*c)[i.i].sgl_cmd[i.j], envc) == 1)
				return (1);
			i.j++;
		}
		if (expand_var_tab(c, envc, i) == 1)
			return (1);
		i.i++;
	}
	return (0);
}
