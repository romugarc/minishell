/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_malloc_tab_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:19:21 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	malloc_chain_files(t_cmd **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_inf > 0)
		{
			(*c)[i].flag_in = malloc(sizeof(char) * (*c)[i].nb_inf + 1);
			if (!(*c)[i].flag_in)
				return (1);
		}
		else
			(*c)[i].flag_in = NULL;
		if ((*c)[i].nb_outf > 0)
		{
			(*c)[i].flag_out = malloc(sizeof(char) * (*c)[i].nb_outf + 1);
			if (!(*c)[i].flag_out)
				return (1);
		}
		else
			(*c)[i].flag_out = NULL;
		i++;
	}
	return (0);
}

static int	malloc_tab_fd_files(t_cmd **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_inf > 0)
		{
			(*c)[i].tab_fdin = init_tab_fd((*c)[i].nb_inf);
			if (!(*c)[i].tab_fdin)
				return (1);
		}
		else
			(*c)[i].tab_fdin = NULL;
		if ((*c)[i].nb_outf > 0)
		{
			(*c)[i].tab_fdout = init_tab_fd((*c)[i].nb_outf);
			if (!(*c)[i].tab_fdout)
				return (1);
		}
		else
			(*c)[i].tab_fdout = NULL;
		i++;
	}
	return (0);
}

static int	malloc_t_files(t_cmd **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_inf > 0)
		{
			(*c)[i].tab_inf = malloc(sizeof(char *) * ((*c)[i].nb_inf + 1));
			if (!(*c)[i].tab_inf)
				return (1);
		}
		else
			(*c)[i].tab_inf = NULL;
		if ((*c)[i].nb_outf > 0)
		{
			(*c)[i].tab_outf = malloc(sizeof(char *) * ((*c)[i].nb_outf + 1));
			if (!(*c)[i].tab_outf)
				return (1);
		}
		else
			(*c)[i].tab_outf = NULL;
		i++;
	}
	return (0);
}

int	malloc_tab_files(t_cmd **c, int nb_pipes)
{
	if (malloc_t_files(c, nb_pipes) == 1)
		return (1);
	if (malloc_chain_files(c, nb_pipes) == 1)
		return (1);
	if (malloc_tab_fd_files(c, nb_pipes) == 1)
		return (1);
	return (0);
}
