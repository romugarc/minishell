/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:27:14 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 19:06:01 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_type(t_cmd *comm, int line, t_envlist **envc)
{
	int			i;
	t_envlist	*cpy;

	i = 0;
	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "PATH") == 1)
			break ;
		cpy = cpy->next;
	}
	if (cpy)
		if (strcmp_tof(cpy->var, "PATH") == 1 && !cpy->var)
			return (puterror(comm[line].sgl_cmd[0], NULL, 1, -1));
	if (!cpy)
		return (puterror(comm[line].sgl_cmd[0], NULL, 1, -1));
	while (comm[line].sgl_cmd[0][i])
	{
		if (comm[line].sgl_cmd[0][i] == '/')
			return (puterror(comm[line].sgl_cmd[0], NULL, 1, -1));
		i++;
	}
	return (puterror(comm[line].sgl_cmd[0], NULL, 2, -1));
}
