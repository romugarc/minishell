/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:59:49 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/10 18:07:30 by fsariogl         ###   ########.fr       */
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

char	*get_slash(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ':')
			j++;
		i++;
	}
	new_str = malloc(sizeof(char) * (i + j + 1));
	if (!new_str)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ':')
			new_str[j++] = '/';
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

t_commands	*commands_path(t_commands *comm, int nb_comm, t_envlist *envcpy)
{
	int			i;
	char		*str;
	char		**allpath;
	t_exec		exec;
	t_envlist	*cpy;

	i = 0;
	cpy = envcpy;
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "PATH") == 1)
			break;
		cpy = cpy->next;
	}
	if (!cpy)
		return (comm);
	str = ft_strjoin(cpy->val, "/");
	str = get_slash(str);
	allpath = ft_split(str, ':');
	free(str);
	while (i < nb_comm)
	{
		if (is_it_builtin(comm[i].sgl_cmd[0], &exec) != 1)
			comm[i] = check_comm(comm[i], allpath);
		i++;
	}
	free_char_tab(allpath);
	return (comm);
}
