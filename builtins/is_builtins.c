/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:20:47 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 14:26:29 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	whithout_builtins(t_cmd comm)
{
	if (strcmp_tof(comm.sgl_cmd[0], "/bin/echo") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "echo") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "/usr/bin/cd") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "cd") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "/bin/pwd") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "pwd") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "export") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "unset") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "/usr/bin/env") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "exit") == 1
		|| strcmp_tof(comm.sgl_cmd[0], "env") == 1)
	{
		return (1);
	}
	return (0);
}

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

int	is_it_builtin(char *cmd, t_exec *exec)
{
	(*exec).error = 1;
	if (strcmp_tof(cmd, "/bin/echo") == 1 || strcmp_tof(cmd, "echo") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/usr/bin/cd") == 1 || strcmp_tof(cmd, "cd") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/bin/pwd") == 1 || strcmp_tof(cmd, "pwd") == 1)
		return (1);
	else if (strcmp_tof(cmd, "export") == 1)
		return (1);
	else if (strcmp_tof(cmd, "unset") == 1)
		return (1);
	else if (strcmp_tof(cmd, "/usr/bin/env") || strcmp_tof(cmd, "env") == 1)
		return (1);
	else if (strcmp_tof(cmd, "exit") == 1)
		return (1);
	else
		(*exec).error = 0;
	return (0);
}

int	is_builtins(t_cmd cmd, t_exec *exec, t_envlist **envc, int *oldp)
{
	(*exec).error = 1;
	if (strcmp_tof(cmd.sgl_cmd[0], "/bin/echo") == 1 \
		|| strcmp_tof(cmd.sgl_cmd[0], "echo") == 1)
		return (ft_echo(cmd.sgl_cmd, (*exec), cmd));
	else if (strcmp_tof(cmd.sgl_cmd[0], "/usr/bin/cd") == 1 \
		|| strcmp_tof(cmd.sgl_cmd[0], "cd") == 1)
		return (ft_cd(cmd.sgl_cmd, (*exec).temp, envc));
	else if (strcmp_tof(cmd.sgl_cmd[0], "/bin/pwd") == 1 \
		|| strcmp_tof(cmd.sgl_cmd[0], "pwd") == 1)
		return (ft_pwd((*exec).temp, cmd, (*exec)));
	else if (strcmp_tof(cmd.sgl_cmd[0], "export") == 1)
		return (ft_export(cmd, (*exec), envc, oldp));
	else if (strcmp_tof(cmd.sgl_cmd[0], "unset") == 1)
		return (ft_unset(cmd.sgl_cmd, (*exec).temp, envc, oldp));
	else if (strcmp_tof(cmd.sgl_cmd[0], "/usr/bin/env") \
		|| strcmp_tof(cmd.sgl_cmd[0], "env") == 1)
		return (ft_env(cmd, (*exec), (*envc), (*oldp)));
	else if (strcmp_tof(cmd.sgl_cmd[0], "exit") == 1)
		ft_exit(cmd.sgl_cmd, (*exec).temp);
	else
		(*exec).error = 0;
	return (0);
}
