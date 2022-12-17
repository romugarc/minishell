/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_form_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:44:31 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:26:57 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reinit_somevar(t_inc *i)
{
	i->n = 0;
	i->l_i = 0;
	i->l_j = 0;
	i->l_e = 0;
	i->k = 0;
	i->j = 0;
}

static int	forming_tab2(t_cmd **com, t_f_str f_str, t_inc *i, int *cpy_f)
{
	i->start = find_special_char('6', f_str, i, (*com)[i->i].sgl_cmd[i->j]);
	if (i->start > -1 || *cpy_f == 1)
	{
		if (*cpy_f == 1)
		{
			i->start = 0;
			*cpy_f = 0;
			i->k = 0;
		}
		if (manage_outfile(com, f_str, i, cpy_f) == 1)
			return (1);
	}
	if (*cpy_f == 1 || i->start == -1)
		i->j += 1;
	else
		i->l_j = i->j;
	return (0);
}

int	form_tab2(t_cmd **com, int np)
{
	t_inc	i;
	t_f_str	f_str;
	int		cpy_flag;

	init_inc(&i);
	while (i.i < np)
	{
		reinit_somevar(&i);
		cpy_flag = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_outf)
		{
			if (quotes_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 1));
			if (special_char_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 0));
			if (forming_tab2(com, f_str, &i, &cpy_flag) == 1)
				return (1);
			free(f_str.quotes);
			free(f_str.sp_chars);
		}
		i.i++;
	}
	return (0);
}

static int	forming_tab(t_cmd **com, t_f_str f_str, t_inc *i, int *cpy_f)
{
	i->start = find_special_char('7', f_str, i, (*com)[i->i].sgl_cmd[i->j]);
	if (i->start > -1 || *cpy_f == 1)
	{
		if (*cpy_f == 1)
		{
			i->start = 0;
			*cpy_f = 0;
			i->k = 0;
		}
		if (manage_infile(com, f_str, i, cpy_f) == 1)
			return (1);
	}
	if (*cpy_f == 1 || i->start == -1)
		i->j += 1;
	else
		i->l_j = i->j;
	return (0);
}

int	form_tab(t_cmd **com, int np)
{
	t_inc	i;
	t_f_str	f_str;
	int		cpy_flag;

	init_inc(&i);
	while (i.i < np)
	{
		reinit_somevar(&i);
		cpy_flag = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_inf)
		{	
			if (quotes_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 1));
			if (special_char_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 0));
			if (forming_tab(com, f_str, &i, &cpy_flag) == 1)
				return (1);
			free(f_str.quotes);
			free(f_str.sp_chars);
		}
		i.i++;
	}
	return (0);
}
