/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cat_ex_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:12:36 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/08 16:27:35 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cating_ex_var(char **n_line, char *b_ex, char *a_ex, t_envlist *env)
{
	char	*tmp_line;

	tmp_line = *n_line;
	*n_line = ft_strjoin(*n_line, env->val);
	if (*n_line == NULL)
		return (free_expand(tmp_line, NULL, NULL, NULL));
	free(tmp_line);
	tmp_line = *n_line;
	*n_line = ft_strjoin(*n_line, a_ex);
	if (*n_line == NULL)
		return (free_expand(tmp_line, NULL, NULL, NULL));
	free(tmp_line);
	free(b_ex);
	free(a_ex);
	return (0);
}

static int	cat_ex_var(char *line, t_inc *i, t_envlist *envc, char **new_line)
{
	char	*bef_ex;
	char	*aft_ex;

	bef_ex = ft_strdup_s_to_e(line, i->l_i, i->start);
	if (bef_ex == NULL)
		return (1);
	aft_ex = ft_strdup_s_to_e(line, i->l_e, ft_strlen(line));
	if (aft_ex == NULL)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	if (*new_line != NULL)
		*new_line = ft_strjoin(*new_line, bef_ex);
	else
		*new_line = ft_strdup(bef_ex);
	if (*new_line == NULL)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	if (cating_ex_var(new_line, bef_ex, aft_ex, envc) == 1)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	return (0);
}

int	copy_var(char *line, t_inc *i, t_envlist *envc, char **new_line)
{
	char		*ex_var;
	t_envlist	*tmp;

	ex_var = NULL;
	if (i->l_e > i->start + 1)
	{
		ex_var = ft_strdup_s_to_e(line, i->start + 1, i->l_e);
		if (ex_var == NULL)
			return (1);
		tmp = envc;
		while (tmp != NULL && i->l_j == 0)
		{
			if (ft_strrcmp(ex_var, tmp->var) == 0)
				i->l_j = 1;
			else
				tmp = tmp->next;
		}
	}
	if (i->l_j == 1)
	{
		if (cat_ex_var(line, i, tmp, new_line) == 1)
			return (free_expand(ex_var, NULL, NULL, NULL));
	}
	free(ex_var);
	return (0);
}
