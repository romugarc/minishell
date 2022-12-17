/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:25:44 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 15:47:41 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	refreshing_pwd(char **val, char *path)
{
	int	i;

	if (*val)
		free(*val);
	*val = malloc(sizeof(char) * ft_strlen(path) + 1);
	if (!*val)
	{
		free(path);
		g_errno = 134;
		return (-1);
	}
	i = 0;
	while (path[i])
	{
		(*val)[i] = path[i];
		i++;
	}
	(*val)[i] = '\0';
	return (0);
}

int	refresh_pwd(t_envlist **envc)
{
	char		*path;
	t_envlist	*tmp;

	tmp = (*envc);
	while (tmp)
	{
		if (strcmp_tof(tmp->var, "PWD") == 1)
			break ;
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
	if (refreshing_pwd(&tmp->val, path) == -1)
		return (-1);
	free(path);
	return (0);
}

static int	refreshing_oldp(char **cpyval, char *pwdval)
{
	if (*cpyval)
		free(*cpyval);
	*cpyval = ft_strdup(pwdval);
	if (!*cpyval)
	{
		*cpyval = malloc(sizeof(char));
		if (!*cpyval)
		{
			g_errno = 134;
			return (-1);
		}
		*cpyval[0] = '\0';
	}
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
			break ;
		cpy = cpy->next;
	}
	if (!cpy)
		return (0);
	while (pwd)
	{
		if (strcmp_tof(pwd->var, "PWD") == 1)
			break ;
		pwd = pwd->next;
	}
	if (refreshing_oldp(&cpy->val, pwd->val) == -1)
		return (-1);
	return (0);
}
