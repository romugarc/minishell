/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:02:54 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 15:13:48 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_next_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!str[0])
		return (0);
	if (str[0] == '-' && str[1] == 'n')
		i = 2;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo_first_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (1);
	if (!str[0])
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
	}
	if (str[0] != '-' && str[1] != 'n')
		return (1);
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	set_fd(t_exec exec, int fdout)
{
	int	out;

	if (exec.nb_comm == 1)
		out = fdout;
	else if (exec.temp < exec.nb_comm)
		out = 1;
	else
		out = 0;
	return (out);
}

int	ft_echo(char **tab, t_exec exec, t_cmd cmd)
{
	int	line;
	int	out;

	line = 1;
	out = set_fd(exec, cmd.fdout);
	while (tab[line])
	{
		if (ft_echo_next_n(tab[line]) == 0)
			break ;
		line++;
	}
	while (tab[line])
	{
		ft_putstr_fd(tab[line++], out);
		if (tab[line])
			ft_putchar_fd(' ', out);
	}
	if (ft_echo_first_n(tab[1]) == 1)
		ft_putchar_fd('\n', out);
	if (out > 2)
		close(out);
	if (exec.temp != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
