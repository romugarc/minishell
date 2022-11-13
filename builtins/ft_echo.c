/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:02:54 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/13 14:57:57 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_next_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!str[1])
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
	if (!str[0])
		return (1);
	if (!str[1])
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	ft_echo(char **tab, int nb_comm)
{
	int	line;

	line = 1;
	if (!tab[1])
		return (1);
	while (ft_echo_next_n(tab[line]) == 1)
		line++;
	while (tab[line])
	{
		ft_putstr_fd(tab[line++], 1);
		if (tab[line])
			ft_putchar_fd(' ', 1);
	}
	if (ft_echo_first_n(tab[1]) == 1)
		ft_putchar_fd('\n', 1);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
