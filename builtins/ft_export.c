/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:06:54 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/27 16:38:52 by fsariogl         ###   ########.fr       */
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

int	ft_lstlen(t_envlist *lst)
{
	int			i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	print_export(t_envlist *envc)
{
	int			nbr;
	t_envlist	*ref;
	t_envlist	*new;
	t_envlist	*limit;
	t_envlist	*max_limit;

	nbr = 0;
	new = envc;
	ref = envc;
	while (new)
	{
		if (ft_strcmp(ref->var, new->var) > 0)
			ref = new;
		new = new->next;
	}
	new = envc;
	max_limit = envc;
	while (new)
	{
		if (ft_strcmp(max_limit->var, new->var) < 0)
			max_limit = new;
		new = new->next;
	}
	limit = ref;
	while (nbr < ft_lstlen(envc))
	{
		nbr = nbr + 1;
		new = envc;
		while (new)
		{
			if (ft_strcmp(limit->var, new->var) < 0 && ft_strcmp(ref->var, new->var) > 0)
				ref = new;
			new = new->next;
		}
		limit = ref;
		if (envc->env_ == 0 || strcmp_tof(ref->var, "_") == 0)
		{
			printf("declare -x %s", ref->var);
			if (ref->equal == 0)
				printf("\n");
			else if (ref->equal == 1 && !ref->val)
				printf("=\"\"\n");
			else
				printf("=\"%s\"\n", ref->val);
		}
		ref = max_limit;
	}
}

int	ft_export(char **comm, int nb_comm, t_envlist **envc)
{
	int		i;

	i = 1;
	if (!comm)
		return (-1);
	if (!comm[1])
		print_export((*envc));
	else
	{
		while (comm[i])
		{
			if (valid_id(comm[i], "export") == 1)
				ft_lstadd_back_env(envc, ft_lstnew_env(comm, i));
			i++;
		}
	}
	if (nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}