/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:58:28 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 17:37:46 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
