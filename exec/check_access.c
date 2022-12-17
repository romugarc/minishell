/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:02:12 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 19:04:21 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_access_next(t_envlist *cpy, t_cmd comm)
{
	search_var(&cpy, "PATH");
	if (cpy)
	{
		if (cpy->val)
			if (cpy->val[0] != '\0')
				if (is_it_path(comm.sgl_cmd[0]) == 0)
					return (puterror(comm.sgl_cmd[0], NULL, 2, -1));
	}
	else if (access(comm.sgl_cmd[0], F_OK | X_OK) == -1)
	{
		g_errno = 1;
		return (puterror(comm.sgl_cmd[0], NULL, 1, -1));
	}
	return (0);
}

int	check_access(t_cmd comm, t_envlist **envc)
{
	int			ret;
	t_envlist	*cpy;

	cpy = (*envc);
	if (comm.sgl_cmd == NULL)
		return (-1);
	if (comm.sgl_cmd[0] == NULL)
		return (-1);
	if (comm.sgl_cmd[0][0] != '\0')
	{
		ret = access(comm.sgl_cmd[0], F_OK);
		if ((ret == -1 || is_command_path(comm, envc) == -1)
			&& whithout_builtins(comm) == 0)
		{
			if (check_access_next(cpy, comm) == -1)
				return (-1);
		}
	}
	else
		return (puterror(comm.sgl_cmd[0], NULL, 2, -1));
	return (0);
}
