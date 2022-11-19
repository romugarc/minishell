/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:59:49 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/19 16:44:01 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	new_comm(t_commands comm, char *temp)
{
	int	i;

	i = 0;
	free(comm.sgl_cmd[0]);
	comm.sgl_cmd[0] = ft_strdup(temp);
	return (comm);
}

t_commands	check_comm(t_commands comm, char **allpath)
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
			comm = new_comm(comm, temp);
		free(temp);
		j++;
	}
	return (comm);
}

t_commands	*commands_path(t_commands *comm, int nb_comm)
{
	int		i;
	char	*str;
	char	**allpath;

	i = 0;
	str = ft_strjoin("/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/:",
		"/usr/local/munki/:/opt/X11/bin/");
	allpath = ft_split(str, ':');
	free(str);
	while (i < nb_comm)
	{
		comm[i] = check_comm(comm[i], allpath);
		i++;
	}
	free_char_tab(allpath);
	return (comm);
}
