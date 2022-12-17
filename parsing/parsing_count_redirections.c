/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:14:54 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 13:08:04 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(t_cmd *c, char *str, t_f_str f_str, int *k)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '>')
				c->nb_outf += 1;
		}
		else if (str[i] == '<' && f_str.quotes[*k] == '0')
		{
			if (str[i + 1] != '<')
				c->nb_inf += 1;
		}
		i++;
		*k += 1;
	}
	return (0);
}

void	count_redirections(t_cmd **commands, int np, t_f_str f_str)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (++i < np)
	{
		j = 0;
		while ((*commands)[i].sgl_cmd[j] != 0)
		{
			while ((f_str.sp_chars[k] == '5' || \
					f_str.sp_chars[k] == '9') && f_str.quotes[k] == '0')
				k++;
			if (f_str.quotes[k] != '\0')
				is_redir(&(*commands)[i], (*commands)[i].sgl_cmd[j], f_str, &k);
			j++;
		}
	}
}
