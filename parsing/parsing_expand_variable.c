/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/10 19:33:22 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	searching_expand(char *line, t_inc *i, t_f_str f_str)
{
	i->start = i->i;
	i->i += 1;
	i->l_e = i->i;
	while (is_in_quotes(f_str, i->i) == i->n \
		&& ft_isenvarc(line[i->l_e]) == 1 && line[i->l_e] != '\0')
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

static int	search_expand(char **line, t_envlist *envc)
{
	t_inc	i;
	t_f_str	f_str;
	char	*new_line;

	init_inc(&i);
	quotes_flags(&f_str, *line);
	special_char_flags(&f_str, *line);
	new_line = NULL;
	while ((*line)[i.i] != '\0')
	{
		i.l_j = 0;
		i.n = is_in_quotes(f_str, i.i);
		if ((*line)[i.i] == '$' && i.n != 1)
		{
			searching_expand(*line, &i, f_str);
			if (copy_var(*line, &i, envc, &new_line) == 1)
				return (1);
			i.l_i = i.l_e;
			break;
		}
		i.i++;
	}
	swap_free(line, new_line);
	free_expand(f_str.quotes, f_str.sp_chars, NULL, NULL);
	return (0);
}

static int	expand_var_tab(t_commands **cmd, t_envlist *envc, t_inc i)
{
	if ((*cmd)[i.i].nb_infile > 0)
	{
		i.j = 0;
		while ((*cmd)[i.i].tab_infile[i.j] != NULL)
		{
			if ((*cmd)[i.i].flag_in[i.j] == '0')
			{
				if (search_expand(&(*cmd)[i.i].tab_infile[i.j], envc) == 1)
					return (1);
			}
			i.j++;
		}
	}
	if ((*cmd)[i.i].nb_outfile > 0)
	{
		i.j = 0;
		while ((*cmd)[i.i].tab_outfile[i.j] != NULL)
		{
			if (search_expand(&(*cmd)[i.i].tab_outfile[i.j], envc) == 1)
				return (1);
			i.j++;
		}
	}
	return (0);
}

int expand_variable(t_commands **c, int np, t_envlist *envc)
{
	t_inc	i;
	t_f_str	f_str;

	init_inc(&i);
	while (i.i < np)
	{
		i.j = 0;
		while ((*c)[i.i].sgl_cmd[i.j] != NULL)
		{
			if (search_expand(&(*c)[i.i].sgl_cmd[i.j], envc) == 1)
				return (1);
			quotes_flags(&f_str, (*c)[i.i].sgl_cmd[i.j]);
			if (expand_search((*c)[i.i].sgl_cmd[i.j], f_str) == 1)
				i.j++;
			free(f_str.quotes);
		}
		if (expand_var_tab(c, envc, i) == 1)
			return (1);
		i.i++;
	}
	return (0);
}
