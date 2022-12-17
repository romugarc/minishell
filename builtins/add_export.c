/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:03:50 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:20:48 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lstnew_export(t_envlist **new_lst, char *new_var, char c)
{
	t_envlist	*cpy;

	cpy = malloc(sizeof(t_envlist));
	if (!cpy)
		return (-1);
	cpy->var = export_varstr(new_var, c);
	cpy->equal = is_equal(new_var);
	cpy->val = export_valstr(new_var);
	cpy->next = NULL;
	(*new_lst) = cpy;
	return (0);
}

static int	ft_strndup_addr(char *new_var, char **var_only, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	while (new_var[i] && new_var[i] != c)
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	if (!tmp)
		return (-1);
	i = 0;
	while (new_var[i] && new_var[i] != c)
	{
		tmp[i] = new_var[i];
		i++;
	}
	tmp[i] = '\0';
	(*var_only) = tmp;
	return (0);
}

static int	add_export_next(t_envlist **cpy, char *new_var, char c)
{
	if (!(*cpy)->val)
	{
		if (get_new_val(cpy, new_var, c) == -1)
			return (-1);
	}
	else
		if (get_next_val(cpy, new_var, c) == -1)
			return (-1);
	return (0);
}

int	add_export(t_envlist **envc, char *new_var, char c)
{
	t_envlist	*cpy;
	t_envlist	*new_lst;
	char		*var_only;

	cpy = (*envc);
	if (ft_strndup_addr(new_var, &var_only, c) == -1)
		return (-1);
	search_var(&cpy, var_only);
	free(var_only);
	if (!cpy)
	{
		if (ft_lstnew_export(&new_lst, new_var, c) == -1)
			return (-1);
		ft_lstadd_back_env(envc, new_lst);
	}
	else
		if (add_export_next(&cpy, new_var, c) == -1)
			return (-1);
	return (0);
}
