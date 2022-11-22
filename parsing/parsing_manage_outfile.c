/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manage_infile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:30:19 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/22 19:28:39 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strdup_s_to_e(char const *src, size_t n, size_t index)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * ((index - n) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[n] && n < index)
	{
		dest[i] = src[n];
		n++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	manage_outfile3(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
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
		i->n += 1;
	}
}

static void	manage_outfile2(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
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
		i->n += 1;
	}
}

void	manage_outfile(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
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
		manage_outfile2(com, f_str, i, start);
	else if (f_str->sp_chars[i->k + 1] != '\0')
		manage_outfile3(com, f_str, i, start);
	if (i->n == (*com)[i->i].nb_outfile)
	{
		(*com)[i->i].tab_outfile[i->n] = NULL;
		(*com)[i->i].flag_out[i->n] = '\0';
	}
}
