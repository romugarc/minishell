/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:01:42 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:30:21 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lstlen(t_envlist *lst)
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

static void	prnt(t_envlist **n, t_envlist **ref, t_envlist **ml, t_envlist *e)
{
	(*n) = e;
	(*ref) = e;
	while ((*n))
	{
		if (ft_strcmp((*ref)->var, (*n)->var) > 0)
			(*ref) = (*n);
		(*n) = (*n)->next;
	}
	(*n) = e;
	(*ml) = e;
	while ((*n))
	{
		if (ft_strcmp((*ml)->var, (*n)->var) < 0)
			(*ml) = (*n);
		(*n) = (*n)->next;
	}
}

static void	prnt_2(t_envlist *ref, t_envlist *envc, int oldp_stat, int out)
{
	if (envc->env_ == 0 || strcmp_tof(ref->var, "_") == 0)
	{
		if (!(strcmp_tof(ref->var, "PWD") == 1 && oldp_stat == -1))
		{
			ft_putstr_fd("declare -x ", out);
			ft_putstr_fd(ref->var, out);
			if (ref->equal == 0)
				ft_putchar_fd('\n', out);
			else if (ref->equal == 1 && !ref->val)
				ft_putstr_fd("=\"\"\n", out);
			else
			{
				ft_putstr_fd("=\"", out);
				ft_putstr_fd(ref->val, out);
				ft_putstr_fd("\"\n", out);
			}
		}
	}
}

static int	prnt_compare(t_envlist *limit, t_envlist *new, t_envlist *ref)
{
	if (ft_strcmp(limit->var, new->var) < 0 \
		&& ft_strcmp(ref->var, new->var) > 0)
		return (1);
	return (0);
}

void	print_export(t_envlist *envc, int oldp_stat, int out)
{
	int			nbr;
	t_envlist	*ref;
	t_envlist	*new;
	t_envlist	*limit;
	t_envlist	*max_limit;

	nbr = 0;
	prnt(&new, &ref, &max_limit, envc);
	limit = ref;
	while (nbr < ft_lstlen(envc))
	{
		nbr = nbr + 1;
		new = envc;
		while (new)
		{
			if (prnt_compare(limit, new, ref) == 1)
				ref = new;
			new = new->next;
		}
		limit = ref;
		prnt_2(ref, envc, oldp_stat, out);
		ref = max_limit;
	}
}
