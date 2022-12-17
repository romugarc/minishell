/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:59:49 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 17:38:50 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_slash_next(char *str, char *new_str)
{
	int	i;
	int	j;

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
	return (new_str);
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
	{
		g_errno = 134;
		return (str);
	}
	new_str = get_slash_next(str, new_str);
	free(str);
	return (new_str);
}

int	commands_path_2(t_envlist **cpy, char ***allpath, char **str)
{
	(*str) = ft_strjoin((*cpy)->val, "/");
	if (!(*str))
	{
		g_errno = 134;
		return (-1);
	}
	(*str) = get_slash((*str));
	if (!(*str))
	{
		g_errno = 134;
		return (-1);
	}
	(*allpath) = ft_split((*str), ':');
	if (!(*allpath))
	{
		g_errno = 134;
		free(*str);
		return (-1);
	}
	return (0);
}

void	commands_path_3(t_cmd **comm, int nb_comm, char **allpath)
{
	int		i;
	t_exec	exec;

	i = 0;
	while (i < nb_comm)
	{
		if ((*comm)[i].sgl_cmd == NULL)
			i++;
		else if ((*comm)[i].sgl_cmd[0] == NULL)
			i++;
		else if (is_it_builtin((*comm)[i].sgl_cmd[0], &exec) != 1)
		{
			(*comm)[i].sgl_cmd[0] = check_comm((*comm)[i], allpath);
			i++;
		}
		else
			i++;
	}
}

t_cmd	*commands_path(t_cmd *comm, int nb_comm, t_envlist *envcpy)
{
	int			i;
	char		*str;
	char		**allpath;
	t_envlist	*cpy;

	i = 0;
	cpy = envcpy;
	search_var(&cpy, "PATH");
	if (!cpy)
		return (comm);
	if (commands_path_2(&cpy, &allpath, &str) == -1)
		return (NULL);
	free(str);
	commands_path_3(&comm, nb_comm, allpath);
	free_char_tab(allpath);
	return (comm);
}
