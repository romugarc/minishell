/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manage_infile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:30:19 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/08 15:23:52 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	manage_outfile3(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	int	end;

	end = *start + 1;
	i->k += 1;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9' || f_str->sp_chars[i->k] == '6') \
		&& f_str->quotes[i->k] != '0')) && f_str->sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k++;
	}
	i->l_e = end;
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_outfile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start + 1, end);
		if ((*com)[i->i].tab_outfile[i->n] == NULL)
			return (1);
		i->n += 1;
	}
	return (0);
}

static int	manage_outfile2(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	int	end;

	*start = 0;
	end = 0;
	i->j++;
	while ((f_str->sp_chars[i->k] == '6' || f_str->sp_chars[i->k] == '9')\
		&& f_str->sp_chars[i->k] != '\0')
		i->k++;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9'\
		|| f_str->sp_chars[i->k] == '6') && f_str->quotes[i->k] != '0')) &&\
		f_str->sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k++;
	}
	i->l_e = end;
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_outfile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start, end);
		if ((*com)[i->i].tab_outfile[i->n] == NULL)
			return (1);
		i->n += 1;
	}
	return (0);
}

int	manage_outfile(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	if (f_str->sp_chars[i->k + 1] == '6')
	{
		(*com)[i->i].flag_out[i->n] = '1';
		i->k += 1;
		*start += 1;
	}
	else
		(*com)[i->i].flag_out[i->n] = '0';
	if (f_str->sp_chars[i->k + 1] == '9' && f_str->sp_chars[i->k + 1] != '\0')
	{
		if (manage_outfile2(com, f_str, i, start) == 1)
			return (1);
	}
	else if (f_str->sp_chars[i->k + 1] != '\0')
	{
		if (manage_outfile3(com, f_str, i, start) == 1)
			return (1);
	}
	if (i->n == (*com)[i->i].nb_outfile)
	{
		(*com)[i->i].tab_outfile[i->n] = NULL;
		(*com)[i->i].flag_out[i->n] = '\0';
	}
	return (0);
}
