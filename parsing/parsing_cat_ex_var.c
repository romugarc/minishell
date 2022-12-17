/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cat_ex_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:02:49 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:27:09 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cating_ex_varnf(char **n_line, char *b_ex, char *a_ex)
{
	char	*tmp_line;

	tmp_line = NULL;
	*n_line = ft_strjoin(b_ex, a_ex);
	if (*n_line == NULL)
		return (free_expand(tmp_line, NULL, NULL, NULL));
	free(b_ex);
	free(a_ex);
	return (0);
}

static int	cating_ex_var(char **n_line, char *b_ex, char *a_ex, char *envstr)
{
	char	*tmp_line;

	tmp_line = NULL;
	*n_line = ft_strjoin(b_ex, envstr);
	if (*n_line == NULL)
		return (free_expand(tmp_line, NULL, NULL, NULL));
	if (tmp_line != NULL)
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

int	cat_ex_varnf(char *line, t_inc *i, char **new_line)
{
	char	*bef_ex;
	char	*aft_ex;

	bef_ex = ft_strdup_s_to_e(line, i->l_i, i->start);
	if (bef_ex == NULL)
		return (1);
	aft_ex = ft_strdup_s_to_e(line, i->l_e, ft_strlen(line));
	if (aft_ex == NULL)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	if (cating_ex_varnf(new_line, bef_ex, aft_ex) == 1)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	return (0);
}

int	cat_ex_var(char *line, t_inc *i, char *envstr, char **new_line)
{
	char	*bef_ex;
	char	*aft_ex;

	if (!envstr)
		return (1);
	bef_ex = ft_strdup_s_to_e(line, i->l_i, i->start);
	if (bef_ex == NULL)
		return (1);
	aft_ex = ft_strdup_s_to_e(line, i->l_e, ft_strlen(line));
	if (aft_ex == NULL)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	if (cating_ex_var(new_line, bef_ex, aft_ex, envstr) == 1)
		return (free_expand(bef_ex, aft_ex, NULL, NULL));
	return (0);
}
