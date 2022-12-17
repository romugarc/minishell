/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:37:13 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:27:24 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_err_fd(t_cmd **cmd, int i, char *str, int mode)
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
	(*cmd)[i].fdin = -1;
	(*cmd)[i].fdout = -1;
	return (1);
}

static int	check_fdout(t_cmd **cmd, int i, int j)
{
	if ((*cmd)[i].flag_out[j] == '0' && (*cmd)[i].tab_fdout != NULL)
	{
		if (access((*cmd)[i].tab_outf[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_outf[j], W_OK) != 0)
				return (print_err_fd(cmd, i, (*cmd)[i].tab_outf[j], 1));
		}
		else if ((*cmd)[i].tab_outf[j][0] == '\0')
			return (print_err_fd(cmd, i, (*cmd)[i].tab_outf[j], 2));
	}
	else if ((*cmd)[i].flag_out[j] == '1' && (*cmd)[i].tab_fdout != NULL)
	{
		if (access((*cmd)[i].tab_outf[j], F_OK) == 0)
		{
			if (access((*cmd)[i].tab_outf[j], W_OK) != 0)
				return (print_err_fd(cmd, i, (*cmd)[i].tab_outf[j], 1));
		}
		else if ((*cmd)[i].tab_outf[j][0] == '\0')
			return (print_err_fd(cmd, i, (*cmd)[i].tab_outf[j], 2));
	}
	return (0);
}

static int	check_fdin(t_cmd **cmd, t_inc i)
{
	if ((*cmd)[i.i].flag_in[i.j] == '0' && (*cmd)[i.i].tab_fdin != NULL)
	{
		if (access((*cmd)[i.i].tab_inf[i.j], F_OK) == 0)
		{
			if (access((*cmd)[i.i].tab_inf[i.j], R_OK) != 0)
				return (print_err_fd(cmd, i.i, (*cmd)[i.i].tab_inf[i.j], 1));
		}
		else
			return (print_err_fd(cmd, i.i, (*cmd)[i.i].tab_inf[i.j], 2));
	}
	return (0);
}

static int	check_fdnorm(t_cmd **cmd, t_inc *i, int mode)
{
	t_inc	inc;

	inc.i = i->i;
	if (mode == 1)
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_inf[inc.j] != 0)
		{
			if (check_fdin(cmd, inc) == 1)
				return (1);
			inc.j++;
		}
	}
	else
	{
		inc.j = 0;
		while ((*cmd)[inc.i].tab_outf[inc.j] != 0)
		{
			if (check_fdout(cmd, inc.i, inc.j) == 1)
				return (1);
			inc.j++;
		}
	}
	return (0);
}

int	check_fd(t_cmd **cmd, int np)
{
	t_inc	inc;

	inc.i = -1;
	while (++inc.i < np)
	{
		if ((*cmd)[inc.i].nb_inf > 0)
			check_fdnorm(cmd, &inc, 1);
		if ((*cmd)[inc.i].nb_outf > 0)
			check_fdnorm(cmd, &inc, 0);
	}
	return (0);
}
