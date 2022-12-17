/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:58:28 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 11:20:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envc(t_envlist *envc)
{
	t_envlist	*cpy;

	while (envc)
	{
		if (envc->val)
			free(envc->val);
		envc->val = NULL;
		if (envc->var)
			free(envc->var);
		envc->var = NULL;
		cpy = envc;
		envc = envc->next;
		free(cpy);
		cpy = NULL;
	}
}

static void	delenv(char *var, char *val)
{
	if (var != NULL)
		free(var);
	if (val != NULL)
		free(val);
}

static void	ft_lstdeltwo(t_envlist *lst)
{
	if (!lst)
		return ;
	delenv(lst->var, lst->val);
	free(lst);
}

void	ft_lstclear_v2(t_envlist **lst)
{
	t_envlist	*cpy;

	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		cpy = *lst;
		*lst = cpy->next;
		ft_lstdeltwo(cpy);
	}
	*lst = NULL;
}
