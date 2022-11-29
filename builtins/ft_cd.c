/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:56:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/29 19:04:33 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_oldpwd(t_envlist **envc)
{
	int			i;
	t_envlist	*tmp;

	i = 0;
	tmp = (*envc);
	while (tmp)
	{
		if (strcmp_tof(tmp->var, "PWD") == 1)
			break;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	(*envc)->oldpwd = malloc(sizeof(char *) * 2);
	if (!(*envc)->oldpwd)
		return (-1);
	(*envc)->oldpwd[0] = ft_strjoin("OLDPWD=", tmp->val);
	if ((*envc)->oldpwd[0] == NULL)
	{
		free((*envc)->oldpwd);
		return (-1);
	}
	(*envc)->oldpwd[1] = NULL;
	return (1);
}

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
		return (-1);
	if (tmp->val)
		free(tmp->val);
	path = getcwd(path, 10000000);
	i = 0;
	while (path[i])
		i++;
	tmp->val = malloc(sizeof(char) * i + 1);
	if (!tmp->val)
		return (-1);
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

int	ft_cd(char **tab, int nb_comm, t_envlist **envc)
{
	int	stat;

	stat = get_oldpwd(envc);
	if (stat == -1)
		return (-1);
	if (chdir(tab[1]) != -1)
	{
		if ((*envc)->is_oldpwd == 0 && stat == 1)
		{
			ft_lstadd_back_env(envc, (ft_lstnew_env((*envc)->oldpwd, 0)));
			(*envc)->is_oldpwd = 1;
			free_char_tab((*envc)->oldpwd);
		}
		refresh_pwd(envc);
	}
	else
		perror(tab[1]);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
