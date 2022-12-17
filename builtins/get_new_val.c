/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:06:49 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:07:09 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_new_val_next(char *new_val, t_envlist **cpy, int i)
{
	int	envi;

	envi = 0;
	i++;
	while (new_val[i])
	{
		(*cpy)->val[envi] = new_val[i];
		envi++;
		i++;
	}
	(*cpy)->val[envi] = '\0';
}

int	get_new_val(t_envlist **envc, char *new_val, char c)
{
	int			i;
	t_envlist	*cpy;

	if (is_equal(new_val) == 0)
		return (0);
	cpy = (*envc);
	cpy->equal = 1;
	i = 0;
	cpy = (*envc);
	if (cpy->val)
		free(cpy->val);
	cpy->val = malloc(sizeof(char) * strlen_from_c(new_val, c) + 1);
	if (!cpy->val)
		return (-1);
	while (new_val[i] && new_val[i] != c)
		i++;
	if (c == '+')
		i++;
	get_new_val_next(new_val, &cpy, i);
	(*envc) = cpy;
	return (0);
}
