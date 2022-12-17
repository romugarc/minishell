/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_reform_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:46:21 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 16:15:42 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**reform_tab2(char **sgl_cmd, int n)
{
	t_inc	i;
	char	**new_sgl;

	new_sgl = malloc(sizeof(char *) * (n + 1));
	if (!new_sgl)
		return (NULL);
	i.j = 0;
	i.k = 0;
	while (sgl_cmd[i.j] != 0)
	{
		if (sgl_cmd[i.j][0] != '\0')
		{
			new_sgl[i.k] = ft_strdup(sgl_cmd[i.j]);
			if (new_sgl[i.k] == NULL)
			{
				ft_free_tab(new_sgl);
				return (NULL);
			}
			i.k++;
		}
		i.j++;
	}
	new_sgl[i.k] = NULL;
	return (new_sgl);
}

int	reform_tab(t_cmd **com, int np)
{
	t_inc	i;
	char	**oldtab;

	init_inc(&i);
	while (i.i < np)
	{
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0)
		{
			if ((*com)[i.i].sgl_cmd[i.j][0] != '\0')
				i.n++;
			i.j++;
		}
		oldtab = (*com)[i.i].sgl_cmd;
		(*com)[i.i].sgl_cmd = reform_tab2((*com)[i.i].sgl_cmd, i.n);
		ft_free_tab(oldtab);
		if ((*com)[i.i].sgl_cmd == NULL)
			return (1);
		i.i++;
	}
	return (0);
}
