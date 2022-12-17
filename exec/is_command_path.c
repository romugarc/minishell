/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:33:15 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 11:00:59 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sec_check_comm(t_cmd comm, char **allpath)
{
	int		j;
	int		res;
	char	*temp;

	j = 0;
	res = -1;
	while (allpath[j] && res == -1)
	{
		temp = ft_strjoin(allpath[j], comm.sgl_cmd[0]);
		res = access(temp, F_OK);
		if (res == 0)
			comm.sgl_cmd[0] = new_comm(comm.sgl_cmd[0], temp);
		free(temp);
		j++;
	}
	if (!allpath[j])
		return (ft_free_tab(allpath));
	ft_free_tab(allpath);
	return (0);
}

int	is_command_path(t_cmd cmd, t_envlist **envc)
{
	t_envlist	*cpy;
	char		*str;
	char		**path;

	cpy = (*envc);
	search_var(&cpy, "PATH");
	if (!cpy)
		return (-1);
	str = ft_strjoin(cpy->val, "/");
	str = get_slash(str);
	path = ft_split(str, ':');
	free(str);
	if (cmd.sgl_cmd == NULL)
		return (ft_free_tab(path));
	if (cmd.sgl_cmd[0] == NULL)
		return (ft_free_tab(path));
	if (whithout_builtins(cmd) == 0)
		return (sec_check_comm(cmd, path));
	ft_free_tab(path);
	return (0);
}
