/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_form_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:44:31 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/26 19:18:14 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	forming_tab2(t_commands **com, t_f_str *f_str, t_inc *i)
{
	int	start;

	while ((f_str->sp_chars[i->k] == '5' \
			|| f_str->sp_chars[i->k] == '9') \
			&& f_str->quotes[i->k] == '0')
		i->k += 1;
	start = find_special_char('6', *f_str, i, (*com)[i->i].sgl_cmd[i->j]);
	if (start > -1)
	{
		if (manage_outfile(com, f_str, i, &start) == 1)
			return (1);
	}
	if (((*com)[i->i].sgl_cmd[i->j] != 0 
			&& (*com)[i->i].sgl_cmd[i->j][i->l_e] == '\0') || start == -1)
		i->j += 1;
	return (0);
}

int	form_tab2(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_outfile)
		{
			if (forming_tab2(com, &f_str, &i) == 1)
				return (1);
		}
		if ((*com)[i.i].nb_outfile == 0 && f_str.quotes[i.k] != '\0')
			i.k += ft_strlen((*com)[i.i].sgl_cmd[i.j]);
		else if ((*com)[i.i].sgl_cmd[i.j] != 0)
		{
			while(f_str.sp_chars[i.k] != '\0')
			{
				if (f_str.sp_chars[i.k] == '5' && is_in_quotes(f_str, i.k) == 0)
					break;
				i.k += 1;
			}
		}
		else if (f_str.quotes[i.k] != '\0')
		{
			i.k+= 1;
		}
		i.i += 1;
	}
	return (0);
}

static int	forming_tab(t_commands **com, t_f_str *f_str, t_inc *i)
{
	int	start;

	while ((f_str->sp_chars[i->k] == '5' \
			|| f_str->sp_chars[i->k] == '9') \
			&& f_str->quotes[i->k] == '0')
		i->k += 1;
	start = find_special_char('7', *f_str, i, (*com)[i->i].sgl_cmd[i->j]);
	if (start > -1)
	{
		if (manage_infile(com, f_str, i, &start) == 1)
			return (1);
	}
	if (((*com)[i->i].sgl_cmd[i->j] != 0 
			&& (*com)[i->i].sgl_cmd[i->j][i->l_e] == '\0') || start == -1)
		i->j += 1;
	return (0);
}

int	form_tab(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int	j;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_infile)
		{
			if (forming_tab(com, &f_str, &i) == 1)
				return (1);
		}
		if ((*com)[i.i].nb_infile == 0 && f_str.quotes[i.k] != '\0')
			i.k += ft_strlen((*com)[i.i].sgl_cmd[i.j]);
		else if ((*com)[i.i].sgl_cmd[i.j] != 0)
		{
			while(f_str.sp_chars[i.k] != '\0')
			{
				if (f_str.sp_chars[i.k] == '5' && is_in_quotes(f_str, i.k) == 0)
					break;
				i.k += 1;
			}
		}
		else if (f_str.quotes[i.k] != '\0')
		{
			i.k+=1;
		}
		i.i += 1;
	}
/*		it = 0;
		printf("%d\n", np);
		while (it < np)
		{
			j = 0;
			printf("%d\n", (*com)[it].nb_infile);
			while (j < (*com)[it].nb_infile && (*com)[it].nb_infile > 0)
			{
				printf("WATYT\n");
				printf("%s.%d\n", (*com)[it].tab_infile[j], it);
				j++;
			}
			printf("hm\n");
			it++;
		}*/
	return (0);
}
