/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_path_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:14:44 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 17:38:57 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_comm(char *sglcmd, char *temp)
{
	free(sglcmd);
	sglcmd = ft_strdup(temp);
	if (!sglcmd)
		return (NULL);
	return (sglcmd);
}

int	check_comm_next(t_cmd *comm, char **temp)
{
	(*comm).sgl_cmd[0] = new_comm((*comm).sgl_cmd[0], (*temp));
	if (!(*comm).sgl_cmd[0])
	{
		free(*temp);
		g_errno = 134;
		return (-1);
	}
	return (0);
}

char	*check_comm(t_cmd comm, char **allpath)
{
	int		j;
	int		res;
	char	*temp;

	j = 0;
	res = -1;
	while (allpath[j] && res == -1)
	{
		temp = ft_strjoin(allpath[j], comm.sgl_cmd[0]);
		if (!temp)
		{
			g_errno = 134;
			return (NULL);
		}
		res = access(temp, F_OK);
		if (res == 0)
			if (check_comm_next(&comm, &temp) == -1)
				return (NULL);
		free(temp);
		j++;
	}
	return (comm.sgl_cmd[0]);
}
