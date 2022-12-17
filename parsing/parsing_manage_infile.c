/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manage_infile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:30:19 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:29:17 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	manage_infile3(t_cmd **com, t_f_str f_str, t_inc *i)
{
	int	end;

	end = i->start + 1;
	i->k += 1;
	while (((f_str.sp_chars[i->k] < '6' || f_str.sp_chars[i->k] >= '8') \
		|| (f_str.sp_chars[i->k] >= '6' && f_str.quotes[i->k] != '0')) \
		&& f_str.sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k++;
	}
	i->l_e = end;
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		if (f_str.sp_chars[i->start] == '7')
			i->start += 1;
		(*com)[i->i].tab_inf[i->n] = \
					ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], i->start, end);
		if ((*com)[i->i].tab_inf[i->n] == NULL)
			return (1);
		i->n += 1;
	}
	return (0);
}

int	manage_infile(t_cmd **com, t_f_str f_str, t_inc *i, int *cpy_f)
{
	if (f_str.sp_chars[i->k] == '7' && f_str.sp_chars[i->k + 1] == '7')
	{
		(*com)[i->i].flag_in[i->n] = '1';
		i->k += 1;
		i->start += 1;
	}
	else if (f_str.sp_chars[i->k] == '7')
		(*com)[i->i].flag_in[i->n] = '0';
	if ((f_str.sp_chars[i->k] == '7' && f_str.sp_chars[i->k + 1] != '\0') \
		|| f_str.sp_chars[i->k] != '7')
	{
		if (manage_infile3(com, f_str, i) == 1)
			return (1);
	}
	else if (f_str.sp_chars[i->k] == '7' && f_str.sp_chars[i->k + 1] == '\0')
		*cpy_f = 1;
	if (i->n == (*com)[i->i].nb_inf)
	{
		(*com)[i->i].tab_inf[i->n] = NULL;
		(*com)[i->i].flag_in[i->n] = '\0';
	}
	return (0);
}
