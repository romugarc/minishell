/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_correct_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:48:37 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 16:52:58 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else
	{
		while (str[i])
			i++;
		if ((str[i - 1] == '>' || str[i - 1] == '<') && str[i] == '\0')
			return (1);
	}
	return (0);
}

static void	correcting_tab(char	**tab, t_f_str *f_str, int *del_f)
{
	t_inc	i;

	init_inc(&i);
	i.start = find_start_char(*f_str, &i, *tab);
	if (i.start > -1 || *del_f == 1)
	{
		if (*del_f == 0)
			*del_f = set_del_flag(*tab);
		else
		{
			i.start = 0;
			*del_f = set_del_flag(*tab);
		}
		ft_del_str_from_i(*tab, i.start);
	}
}

int	free_flags(t_f_str f_str, int mode)
{
	if (mode == 1)
		free(f_str.quotes);
	else
	{
		free(f_str.quotes);
		free(f_str.sp_chars);
	}
	return (1);
}

int	correct_tab(t_cmd **com, int np)
{
	t_inc	i;
	t_f_str	f_str;
	int		del_flag;

	i.i = 0;
	i.k = 0;
	while (i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.j = 0;
		del_flag = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0)
		{
			if (quotes_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 1));
			if (special_char_flags(&f_str, (*com)[i.i].sgl_cmd[i.j]) == 1)
				return (free_flags(f_str, 0));
			correcting_tab(&(*com)[i.i].sgl_cmd[i.j], &f_str, &del_flag);
			free_flags(f_str, 0);
			i.j++;
		}
		i.i += 1;
	}
	return (0);
}
