/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:42:52 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 15:36:51 by fsariogl         ###   ########.fr       */
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

t_envlist	*ft_lstnew_env(char **envp, int line)
{
	int			i;
	t_envlist	*lst;

	i = 0;
	lst = malloc(sizeof(t_envlist));
	if (!lst)
	{
		g_errno = 134;
		exit(EXIT_FAILURE);
	}
	lst->equal = 0;
	while (envp[line][i])
		if (envp[line][i++] == '=')
			lst->equal = 1;
	lst->var = varstr(envp, line);
	lst->val = valuestr(envp, line);
	if (!lst->var || !lst->val)
	{
		g_errno = 134;
		exit(EXIT_FAILURE);
	}
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

t_envlist	*new_shlvl(void)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
	new->equal = 1;
	new->var = ft_strdup("SHLVL");
	new->val = ft_strdup("1");
	new->next = NULL;
	if (!new->var || !new->val)
	{
		g_errno = 134;
		exit(EXIT_FAILURE);
	}
	return (new);
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
	get_shlvl(&tmp);
	tmp->env_ = 0;
	return (tmp);
}
