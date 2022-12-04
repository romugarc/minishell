/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:42:52 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/01 15:39:18 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envlist	*ft_lstlast_env(t_envlist *lst)
{
	t_envlist	*cpy;

	if (!lst)
		return (NULL);
	cpy = lst;
	while (cpy->next)
		cpy = cpy->next;
	return (cpy);
}

int	strlen_until(char *str, char *until)
{
	int	i;
	int	u;

	i = 0;
	while (str[i])
	{
		u = 0;
		while (until[u])
		{
			if (str[i] == until[u])
				return (i);
			u++;
		}
		i++;
	}
	return (i);
}

int	strlen_from(char *str, char *from)
{
	int	i;
	int	f;
	int	count;

	i = 0;
	count = -2;
	while (str[i])
	{
		f = 0;
		while (from[f])
			if (str[i] == from[f++] && count == -2)
				count = -1;
		i++;
		if (count >= -1)
			count++;
	}
	if (count == -2)
		return (0);
	return (count);
}

char	*varstr(char **envp, int line)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * strlen_until(envp[line], "=") + 1);
	if (!var)
		exit(EXIT_FAILURE);
	while (envp[line][i] && envp[line][i] != '=')
	{
		var[i] = envp[line][i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*valuestr(char **envp, int line)
{
	int		i;
	int		v;
	char	*value;

	i = 0;
	v = 0;
	value = malloc(sizeof(char) * strlen_from(envp[line], "=") + 1);
	if (!value)
		exit(EXIT_FAILURE);
	while (envp[line][i] != '=' && envp[line][i])
		i++;
	if (envp[line][i] == '=')
		i++;
	while (envp[line][i])
	{
		value[v] = envp[line][i];
		i++;
		v++;
	}
	value[v] = '\0';
	return (value);
}

t_envlist	*ft_lstnew_env(char **envp, int line)
{
	int			i;
	t_envlist	*lst;

	i = 0;
	lst = malloc(sizeof(t_envlist));
	if (!lst)
		exit(EXIT_FAILURE);
	lst->equal = 0;
	while (envp[line][i])
		if (envp[line][i++] == '=')
			lst->equal = 1;
	lst->var = varstr(envp, line);
	lst->val = valuestr(envp, line);
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back_env(t_envlist **alst, t_envlist *new_lst)
{
	t_envlist	*cpy;
	if (alst)
	{
		if (*alst)
		{
			cpy = ft_lstlast_env(*alst);
			cpy->next = new_lst;
		}
		else
			*alst = new_lst;
	}
	else
		alst = &new_lst;
}

t_envlist	*envcpy(char **envp)
{
	int			line;
	t_envlist	*tmp;
	static int	first_time = 1;

	if (!envp)
		return (NULL);
	tmp = NULL;
	line = 0;
	while (envp[line])
		ft_lstadd_back_env(&tmp, ft_lstnew_env(envp, line++));
	if (first_time == 1)
		rm_val("OLDPWD", &tmp, &first_time);
	return (tmp);
}
