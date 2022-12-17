/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:36:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:17:46 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	is_equal(char *new_var)
{
	int			i;

	i = 0;
	while (new_var[i] && new_var[i] != '=')
		i++;
	if (new_var[i] == '=')
		return (1);
	return (0);
}

int	check_cmd_fd(t_cmd cmd)
{
	if (cmd.fdin < 0 || cmd.fdout < 0)
	{
		g_errno = 1;
		return (-1);
	}
	return (0);
}

int	is_it_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	search_var(t_envlist **cpy, char *search)
{
	while (*cpy)
	{
		if (strcmp_tof((*cpy)->var, search) == 1)
			break ;
		(*cpy) = (*cpy)->next;
	}
}
