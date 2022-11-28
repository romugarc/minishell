/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_malloc_tab_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 18:29:23 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	malloc_chain_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].flag_in = malloc(sizeof(char) * (*c)[i].nb_infile + 1);
			if (!(*c)[i].flag_in)
				return (1);
		}
		else
			(*c)[i].flag_in = NULL;
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].flag_out = malloc(sizeof(char) * (*c)[i].nb_outfile + 1);
			if (!(*c)[i].flag_out)
				return (1);
		}
		else
			(*c)[i].flag_out = NULL;
		i++;
	}
	return (0);
}

static int	malloc_tab_fd_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].tab_fdin = init_tab_fd((*c)[i].nb_infile);
			if (!(*c)[i].tab_fdin)
				return (1);
		}
		else
			(*c)[i].tab_fdin = NULL;
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_fdout = init_tab_fd((*c)[i].nb_outfile);
			if (!(*c)[i].tab_fdout)
				return (1);
		}
		else
			(*c)[i].tab_fdout = NULL;
		i++;
	}
	return (0);
}

static int	malloc_t_files(t_commands **c, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			(*c)[i].tab_infile = malloc(sizeof(char *) * ((*c)[i].nb_infile + 1));
			if (!(*c)[i].tab_infile)
				return (1);
		}
		else
			(*c)[i].tab_infile = NULL;
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * ((*c)[i].nb_outfile + 1));
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		else
			(*c)[i].tab_outfile = NULL;
		i++;
	}
	return (0);
}

int	malloc_tab_files(t_commands **c, int nb_pipes)
{
	if (malloc_t_files(c, nb_pipes) == 1)
		return (1);
	if (malloc_chain_files(c, nb_pipes) == 1)
		return (1);
	if (malloc_tab_fd_files(c, nb_pipes) == 1)
		return (1);
	return (0);
}
