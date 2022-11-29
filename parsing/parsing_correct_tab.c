/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_correct_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:48:37 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/25 15:58:10 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	update_k(char *str, int i, int ik, t_f_str f_str)
{
	int	k;

	k = ik;
	while (str[i] != '\0' && f_str.quotes[k] != '\0')
	{
		i++;
		k++;
	}
	return (k);
}

static int	find_start_char(t_f_str f_str, t_inc *inc, char *s_c)
{
	int	i;

	i = 0;
	while (f_str.sp_chars[inc->k] != '\0' && s_c[i] != '\0')
	{
		if ((f_str.sp_chars[inc->k] == '7' || f_str.sp_chars[inc->k] == '6') \
			&& f_str.quotes[inc->k] == '0')
		{
				inc->l_i = i;
				return (i);
		}
		inc->k += 1;
		i++;
	}
	inc->l_i = 0;
	return (-1);
}

static int	set_del_flag(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '\0')
		return (1);
	else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
		return (1);
	return (0);
}

static void	correct_tab2(t_commands **com, t_f_str *f_str, t_inc *i, int *del_f)
{
	int	start;

	while ((f_str->sp_chars[i->k] == '5' \
			|| f_str->sp_chars[i->k] == '9') \
			&& f_str->quotes[i->k] == '0')
		i->k += 1;
	start = find_start_char(*f_str, i, (*com)[i->i].sgl_cmd[i->j]);
	if (start > -1 || *del_f == 1)
	{
		if (*del_f == 0)
			*del_f = set_del_flag((*com)[i->i].sgl_cmd[i->j]);
		else
		{
			start = 0;
			*del_f = 0;
		}
		i->k = update_k((*com)[i->i].sgl_cmd[i->j], start, i->k, *f_str);
		ft_del_str_from_i((*com)[i->i].sgl_cmd[i->j], start);
	}
	i->j += 1;
}

int	correct_tab(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int		del_flag;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.j = 0;
		del_flag = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0)
			correct_tab2(com, &f_str, &i, &del_flag);
		if (f_str.quotes[i.k] != '\0')
			i.k += 1;
		i.i += 1;
	}
	return (0);
}
