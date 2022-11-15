/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:20:47 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/13 15:25:34 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *cmd, char *str)
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
	if (ft_strcmp(cmd, "echo") == 1)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 1)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 1)
		return (1);
//	else if (ft_strcmp(cmd, "export") == 1)
//		return (1);
//	else if (ft_strcmp(cmd, "unset") == 1)
//		return (1);
//	else if (ft_strcmp(cmd, "env") == 1)
//		return (1);
//	else if (ft_strcmp(cmd, "exit") == 1)
//		return (1);
	return (0);
}

int	is_builtins(t_commands *comm, t_exec exec, int nb_comm)
{
	if (ft_strcmp(comm[exec.comm_i].single_command[0], "echo") == 1)
	{
		return (ft_echo(comm[exec.comm_i].single_command, nb_comm));
	}
	else if (ft_strcmp(comm[exec.comm_i].single_command[0], "cd") == 1)
	{
		return (ft_cd(comm[exec.comm_i].single_command, nb_comm));
	}
	else if (ft_strcmp(comm[exec.comm_i].single_command[0], "pwd") == 1)
	{
		return (ft_pwd(nb_comm));
	}
//	else if (ft_strcmp(comm.single_command, "export") == 1)
//	else if (ft_strcmp(comm.single_command, "unset") == 1)
//	else if (ft_strcmp(comm.single_command, "env") == 1)
//	else if (ft_strcmp(comm.single_command, exit) == 1)
	return (0);
}