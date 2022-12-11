/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:37:13 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/11 15:51:39 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_err_fd(char *str, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (mode == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (1);
}

static int	check_fdout(t_commands **cmd, int i, int j)
{
	if ((*cmd)[i].flag_out[j] == '0' && (*cmd)[i].tab_fdout != NULL)
	{
		if (access((*cmd)[i].tab_outfile[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_outfile[j], W_OK) != 0)
			{
				print_err_fd((*cmd)[i].tab_outfile[j], 1);
				(*cmd)[i].fdout = -1;
				return (1);
			}
		}
	}
	else if ((*cmd)[i].flag_out[j] == '1' && (*cmd)[i].tab_fdout != NULL)
	{	
		if (access((*cmd)[i].tab_outfile[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_outfile[j], W_OK) != 0)
			{
				print_err_fd((*cmd)[i].tab_outfile[j], 1);
				(*cmd)[i].fdout = -1;
				return (1);
			}
		}
	}
	return (0);
}

static int	check_fdin(t_commands **cmd, t_inc inc)
{
	if ((*cmd)[inc.i].flag_in[inc.j] == '0' && (*cmd)[inc.i].tab_fdin != NULL)
	{
		if (access((*cmd)[inc.i].tab_infile[inc.j], F_OK) == 0)
		{
			if (access((*cmd)[inc.i].tab_infile[inc.j], R_OK) != 0)
			{
				print_err_fd((*cmd)[inc.i].tab_infile[inc.j], 1);
				(*cmd)[inc.i].fdin = -1;
				return (1);
			}
		}
		else
		{
			print_err_fd((*cmd)[inc.i].tab_infile[inc.j], 2);
			(*cmd)[inc.i].fdin = -1;
			return (1);
		}
	}
	return (0);
}

static int	check_fdnorm(t_commands **cmd, t_inc *i, int mode)
{
	t_inc	inc;

	inc.i = i->i;
	if (mode == 1)
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_infile[inc.j] != 0)
		{
			if (check_fdin(cmd, inc) == 1)
				return (1);
			inc.j++;
		}
	}
	else
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_outfile[inc.j] != 0)
		{
			if (check_fdout(cmd, inc.i, inc.j) == 1)
				return (1);
			inc.j++;
		}
	}
	return (0);
}

int	check_fd(t_commands **cmd, int np)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		if ((*cmd)[inc.i].nb_infile > 0)
			check_fdnorm(cmd, &inc, 1);
		if ((*cmd)[inc.i].nb_outfile > 0)
			check_fdnorm(cmd, &inc, 0);
	}
	return (0);
}
