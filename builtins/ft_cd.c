/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:56:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 13:24:06 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	refresh_pwd(t_envlist **envc)
{
	int			i;
	char		*path;
	t_envlist	*tmp;

	tmp = (*envc);
	while (tmp)
	{
		if (strcmp_tof(tmp->var, "PWD") == 1)
			break;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	path = malloc(sizeof(char) * 10000000);
	if (!path)
	{
		g_errno = 134;
		return (-1);
	}
	path = getcwd(path, 10000000);
	if (tmp->val)
		free(tmp->val);
	tmp->val = malloc(sizeof(char) * ft_strlen(path) + 1);
	if (!tmp->val)
	{
		free(path);
		g_errno = 134;
		return (-1);
	}
	i = 0;
	while (path[i])
	{
		tmp->val[i] = path[i];
		i++;
	}
	tmp->val[i] = '\0';
	free(path);
	return (0);
}

int	refresh_oldp(t_envlist **envc)
{
	t_envlist	*cpy;
	t_envlist	*pwd;
	
	cpy = (*envc);
	pwd = (*envc);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "OLDPWD") == 1)
			break;
		cpy = cpy->next;
	}
	if (!cpy)
		return (0);
	while (pwd)
	{
		if (strcmp_tof(pwd->var, "PWD") == 1)
			break;
		pwd = pwd->next;
	}
	if (cpy->val)
		free(cpy->val);
	cpy->val = ft_strdup(pwd->val);
	if (!cpy->val)
	{
		cpy->val = malloc(sizeof(char));
		if (!cpy->val)
		{
			g_errno = 134;
			return (-1);
		}
		cpy->val[0] = '\0';
	}
	return (0);
}

void	oldp_first_time(t_envlist **envc)
{
	t_envlist	*cpy;

	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "OLDPWD") == 1)
		{
			cpy->equal = 1;
			break;
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
