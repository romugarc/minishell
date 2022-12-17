/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cat_ex_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:12:36 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 13:05:47 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	copy_var2(char *line, t_inc *i, t_misc m, char **new_line)
{
	char	*res;

	if (i->l_j == 1)
	{
		if (cat_ex_var(line, i, m.tmp->val, new_line) == 1)
			return (free_expand(m.ex_var, NULL, NULL, NULL));
	}
	else if (line[i->start + 1] == '?')
	{
		res = ft_itoa(g_errno);
		if (cat_ex_var(line, i, res, new_line) == 1)
			return (free_expand(m.ex_var, res, NULL, NULL));
		free(res);
	}
	else if (i->l_e > i->start + 1)
	{
		if (cat_ex_varnf(line, i, new_line) == 1)
			return (free_expand(m.ex_var, NULL, NULL, NULL));
	}
	else
		*new_line = NULL;
	return (0);
}

int	copy_var(char *line, t_inc *i, t_envlist *envc, char **new_line)
{
	t_misc	m;

	m.ex_var = NULL;
	if (i->l_e > i->start + 1)
	{
		m.ex_var = ft_strdup_s_to_e(line, i->start + 1, i->l_e);
		if (m.ex_var == NULL)
			return (1);
		m.tmp = envc;
		while (m.tmp != NULL && i->l_j == 0)
		{
			if (ft_strrcmp(m.ex_var, m.tmp->var) == 0)
				i->l_j = 1;
			else
				m.tmp = m.tmp->next;
		}
	}
	if (copy_var2(line, i, m, new_line) == 1)
		return (1);
	free(m.ex_var);
	return (0);
}
