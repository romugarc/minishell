/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:20:47 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/28 17:57:40 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strcmp_tof(char *cmd, char *str)
{
	int	i;

	i = 0;
	if (cmd[i] == '\0')
		return (-1);
	while (cmd[i] == str[i] && cmd[i] != '\0' && str[i] != '\0')
		i++;
	if (cmd[i] == '\0' && str[i] == '\0')
		return (1);
	return (0);
}

int	is_it_builtin(char *cmd)
{
	if (strcmp_tof(cmd, "/bin/echo") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/usr/bin/cd") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/bin/pwd") == 1)
		return (1);
	else if (strcmp_tof(cmd, "export") == 1)
		return (1);
	else if (strcmp_tof(cmd, "unset") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/usr/bin/env") == 1)
		return (1);
	else if (strcmp_tof(cmd, "exit") == 1)
		return (1);
	return (0);
}

int	is_builtins(char **cmds, int nb_comm, t_envlist **envc)
{
	if (strcmp_tof(cmds[0], "/bin/echo") == 1)
		return (ft_echo(cmds, nb_comm));
	else if (strcmp_tof(cmds[0], "/usr/bin/cd") == 1)
		return (ft_cd(cmds, nb_comm, envc));
	else if (strcmp_tof(cmds[0], "/bin/pwd") == 1)
		return (ft_pwd(nb_comm));
	else if (strcmp_tof(cmds[0], "export") == 1)
		ft_export(cmds, nb_comm, envc);
	else if (strcmp_tof(cmds[0], "unset") == 1)
		return (ft_unset(cmds, nb_comm, envc));
	else if (strcmp_tof(cmds[0], "/usr/bin/env") == 1)
		return (ft_env(cmds, nb_comm, (*envc)));
	else if (strcmp_tof(cmds[0], "exit") == 1)
		ft_exit(cmds, nb_comm);
	return (0);
}
