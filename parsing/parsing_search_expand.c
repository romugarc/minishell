/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_search_expand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:07:28 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 17:34:35 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	searching_expand(char *line, t_inc *i, t_f_str f_str)
{
	i->start = i->i;
	i->i += 1;
	i->l_e = i->i;
	while (is_in_quotes(f_str, i->i) == i->n \
		&& ft_isenvarc(line[i->l_e], 0) == 1 && line[i->l_e] != '\0')
	{
		i->l_e++;
		i->i++;
	}
	if (i->l_e == i->start + 1 && line[i->l_e] == '?')
	{
		i->l_e++;
		i->i++;
	}
	return (0);
}

static int	swap_free(char **line, char *new_line)
{
	char	*tmp_line;

	if (new_line != NULL)
	{
		tmp_line = *line;
		*line = new_line;
		free(tmp_line);
	}
	return (0);
}

static int	srch_xp_rtne(char **line, t_f_str *f, t_envlist *env, char **n_l)
{
	searching_expand(*line, &(*f).i, *f);
	if (copy_var(*line, &(*f).i, env, n_l) == 1)
		return (free_expand(f->quotes, f->sp_chars, NULL, NULL));
	f->i.i = f->i.start;
	swap_free(line, *n_l);
	return (0);
}

static int	flag_the_string(t_f_str *f_str, char *line)
{
	if (quotes_flags(f_str, line) == 1)
		return (1);
	if (special_char_flags(f_str, line) == 1)
		return (1);
	return (0);
}

int	search_expand(char **line, t_envlist *envc)
{
	t_f_str	f_str;
	char	*new_line;

	init_inc(&f_str.i);
	new_line = NULL;
	while ((*line)[f_str.i.i] != '\0')
	{
		if (flag_the_string(&f_str, *line) == 1)
			return (1);
		f_str.i.l_j = 0;
		f_str.i.n = is_in_quotes(f_str, f_str.i.i);
		if ((*line)[f_str.i.i] == '$' && f_str.i.n != 1)
		{
			if (srch_xp_rtne(line, &f_str, envc, &new_line) == 1)
				return (1);
		}
		f_str.i.i++;
		free_expand(f_str.quotes, f_str.sp_chars, NULL, NULL);
		if ((*line)[0] == '\0')
			break ;
	}
	if ((*line)[0] != '\0')
		(*line)[f_str.i.i] = '\0';
	return (0);
}
