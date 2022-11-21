/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manage_infile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:30:19 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/21 19:30:53 by rgarcia          ###   ########lyon.fr   */
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

static void	manage_infile3(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	int	end;

	end = *start + 1;
	i->k += 1;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9' || f_str->sp_chars[i->k] == '7') \
		&& f_str->quotes[i->k] != '0')) && f_str->sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k++;
	}
	i->l_e = end;
//	printf("%d\t%d\n", *start, end);
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_infile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start + 1, end);
//		printf("%s2\n", (*com)[i->i].tab_infile[i->n]);
		i->n += 1;
	}
}

static void	manage_infile2(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	int	end;

	*start = 0;
	end = 0;
	i->j++;
	while ((f_str->sp_chars[i->k] == '7' || f_str->sp_chars[i->k] == '9')\
		&& f_str->sp_chars[i->k] != '\0')
		i->k++;
	while ((f_str->sp_chars[i->k] < '5' || ((f_str->sp_chars[i->k] == '9'\
		|| f_str->sp_chars[i->k] == '7') && f_str->quotes[i->k] != '0')) &&\
		f_str->sp_chars[i->k] != '\0')
	{
		end += 1;
		i->k++;
	}
	i->l_e = end;
//	printf("%d\t%d\n", *start, end);
	if ((*com)[i->i].sgl_cmd[i->j] != 0)
	{
		(*com)[i->i].tab_infile[i->n] = ft_strdup_s_to_e((*com)[i->i].sgl_cmd[i->j], *start, end);
//		printf("%s1\n", (*com)[i->i].tab_infile[i->n]);
		i->n += 1;
	}
}

void	manage_infile(t_commands **com, t_f_str *f_str, t_inc *i, int *start)
{
	if (f_str->sp_chars[i->k + 1] == '7')
	{
		(*com)[i->i].flag_in[i->n] = '1';
		i->k += 1;
		*start += 1;
	}
	else
		(*com)[i->i].flag_in[i->n] = '0';
	if (f_str->sp_chars[i->k + 1] == '9' && f_str->sp_chars[i->k + 1] != '\0')
		manage_infile2(com, f_str, i, start);
	else if (f_str->sp_chars[i->k + 1] != '\0')
		manage_infile3(com, f_str, i, start);
	if (i->n == (*com)[i->i].nb_infile)
	{
		(*com)[i->i].tab_infile[i->n] = NULL;
		(*com)[i->i].flag_in[i->n] = '\0';
	}
}
