/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/04 15:17:16 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_type(t_commands *comm, int line)
{
	int	i;

	i = 0;
	while (comm[line].sgl_cmd[0][i])
	{
		if (comm[line].sgl_cmd[0][i] == '/')
		{
			printf("minishell: %s: No such file or directory\n", comm[line].sgl_cmd[0]);
			return (-1);
		}
		i++;
	}
	printf("minishell: %s: command not found\n",
	comm[line].sgl_cmd[0]);
	return (-1);
}

int	check_access(t_commands *comm, int nb_comm)
{
	int	i;

	i = 0;
	while (i < nb_comm)
	{
		if (comm[i].sgl_cmd[0][0] != '\0')
		{
			if (access(comm[i].sgl_cmd[0], F_OK) == -1
				&& strcmp_tof(comm[i].sgl_cmd[0], "export") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "unset") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "exit") != 1)
			{
				if (errno == 2)
					return (error_type(comm, i));
				return (-1);
			}
			if (access(comm[i].sgl_cmd[0], X_OK) == -1
				&& strcmp_tof(comm[i].sgl_cmd[0], "unset") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "export") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "exit") != 1)
				return (-1);
		}
		i++;
	}
	return (0);
}

void	wait_all_cpid(pid_t *cpid, int status, int i)
{
	int	temp;

	temp = 0;
	status = 0;
	while (temp <= i)
	{
		waitpid(cpid[temp], &status, 0);
		temp++;
	}
}

int	pipe_error_case(int nb_comm, t_exec exec)
{
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i);
	free(exec.cpid);
	free_char_tab_ret(exec);
	free_tab(exec.fd, exec.comm_i);
	return (-1);
}

// rm -rf ../../../a
// SHLVL

int	exec_main(t_commands *commands, int nb_comm, t_envlist **envc)
{
	t_exec		exec;
	static int	oldp_stat = 0;

	if (nb_comm < 1)
		return (-1);
//	if (check_access(commands, nb_comm) == -1)
//		return (-1);
	if (get_tmp_env(envc, &exec) == -1)
		return (free_char_tab_ret(exec));
	if (exec_init(&exec, nb_comm) == -1)
		return (free_char_tab_ret(exec));
	if (nb_comm == 1)
		is_builtins(commands[exec.comm_i].sgl_cmd, nb_comm, envc, &oldp_stat);
	exec.nb_comm = nb_comm;
	(*envc)->env_ = 1;
	while (exec.temp > 0 && (nb_comm > 1
			|| is_it_builtin(commands[0].sgl_cmd[0]) != 1))
	{
		if (exec.temp > 1)
			if (pipe(exec.fd[exec.comm_i]) == -1)
				return (pipe_error_case(nb_comm, exec));
		exec.cpid[exec.comm_i] = fork();
		if (exec.cpid[exec.comm_i] == 0)
			child_process(commands, exec, envc, &oldp_stat);
		exec.comm_i++;
		exec.temp--;
	}
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i - 1);
	free_char_tab_ret(exec);
	wait_all_cpid(exec.cpid, exec.status, exec.comm_i);
	free_all(exec, nb_comm);
	return (0);
}
