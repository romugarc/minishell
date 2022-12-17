/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:56:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 20:27:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	oldp_first_time(t_envlist **envc)
{
	t_envlist	*cpy;

	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "OLDPWD") == 1)
		{
			cpy->equal = 1;
			break ;
		}
		cpy = cpy->next;
	}
}

int	ft_cd(char **tab, int nb_comm, t_envlist **envc)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (chdir(tab[1]) != -1 && path != NULL)
	{
		oldp_first_time(envc);
		if (refresh_oldp(envc) == -1 || refresh_pwd(envc) == -1)
		{
			if (path)
				free(path);
			return (-1);
		}
		g_errno = 0;
	}
	else
	{
		g_errno = 1;
		perror(tab[1]);
	}
	if (path)
		free(path);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
