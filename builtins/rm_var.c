/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:30:16 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 11:32:48 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_envlist(t_envlist *envc)
{
	free(envc->var);
	if (envc->val)
		free(envc->val);
	free(envc);
}

static void	removing_var(t_envlist **cpy, t_envlist **sec_cpy, char *var)
{
	while ((*cpy)->next)
	{
		if (strcmp_tof(var, (*cpy)->next->var) == 1)
		{
			if ((*cpy)->next->next)
				*sec_cpy = (*cpy)->next->next;
			free_envlist((*cpy)->next);
			if (*sec_cpy)
				(*cpy)->next = *sec_cpy;
			else
				(*cpy)->next = NULL;
		}
		if ((*cpy)->next)
			*cpy = (*cpy)->next;
	}
}

void	rm_var(char *var, t_envlist **envc)
{
	t_envlist	*cpy;
	t_envlist	*sec_cpy;

	if (!(*envc) || !var)
		return ;
	cpy = (*envc);
	if (strcmp_tof(var, cpy->var) == 1)
	{
		sec_cpy = cpy->next;
		free_envlist(cpy);
		cpy = sec_cpy;
		(*envc) = cpy;
	}
	if (!cpy)
		return ;
	if (!cpy->next)
		return ;
	sec_cpy = NULL;
	removing_var(&cpy, &sec_cpy, var);
}
