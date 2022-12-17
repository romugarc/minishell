/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:23:21 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 19:24:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_shlvl_next(t_envlist **cpy)
{
	{
		(*cpy)->equal = 1;
		(*cpy)->val = ft_strdup("1");
		if (!(*cpy)->val)
		{
			g_errno = 134;
			exit(EXIT_FAILURE);
		}
	}
	return (-1);
}

int	get_shlvl(t_envlist **envc)
{
	char		*tmp;
	t_envlist	*cpy;

	cpy = (*envc);
	search_var(&cpy, "SHLVL");
	if (cpy)
	{
		if (cpy->val)
		{
			cpy->equal = 1;
			tmp = cpy->val;
			if (ft_atoi(cpy->val) < 0)
				cpy->val = ft_itoa(0);
			else
				cpy->val = ft_itoa(ft_atoi(cpy->val) + 1);
			free(tmp);
		}
		else
			get_shlvl_next(&cpy);
	}
	else
		ft_lstadd_back_env(envc, new_shlvl());
	return (0);
}
