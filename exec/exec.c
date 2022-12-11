/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/11 15:15:08 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd_fd(t_commands cmd)
{
	if (cmd.fdin < 0 || cmd.fdout < 0)
		return (-1);
	return (0);
}

int	error_type(t_commands *comm, int line, t_envlist **envc)
{
	int			i;
	t_envlist	*cpy;

	i = 0;
	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(cpy->var, "PATH") == 1)
			break;
		cpy = cpy->next;
	}
		printf("%s\n", cpy->var);
	if (cpy)
	{
		if (strcmp_tof(cpy->var, "PATH") == 1 && !cpy->var)
		{
			printf("minishell: %s: No such file or directory\n", comm[line].sgl_cmd[0]);
			return (-1);
		}
	}
	else if (!cpy)
		printf("minishell: %s: No such file or directory\n", comm[line].sgl_cmd[0]);
			return (-1);
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

int	check_access(t_commands *comm, int nb_comm, t_envlist **envc)
{
	int			i;

	i = 0;
	while (i < nb_comm)
	{
		if (comm[i].sgl_cmd[0][0] != '\0')
		{
			if (access(comm[i].sgl_cmd[0], F_OK) == -1
				&& strcmp_tof(comm[i].sgl_cmd[0], "export") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "unset") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "exit") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "env") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "pwd") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "cd") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "echo") != 1)
			{
				if (errno == 2)
					return (error_type(comm, i, envc));
				return (-1);
			}
			if (access(comm[i].sgl_cmd[0], X_OK) == -1
				&& strcmp_tof(comm[i].sgl_cmd[0], "unset") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "export") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "exit") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "env") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "pwd") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "cd") != 1
				&& strcmp_tof(comm[i].sgl_cmd[0], "echo") != 1)
			{	
				printf("access denied\n");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	wait_all_cpid(pid_t *cpid, int status, int i, t_exec *exec)
{
	int	temp;

	temp = 0;
	status = 0;
	while (temp <= i)
	{
		waitpid(cpid[temp], &status, 0);
		temp++;
	}
	if ((*exec).error == 0)
		g_errno = status / 256;
	(*exec).error = 0;
}

int	pipe_error_case(int nb_comm, t_exec exec, t_commands *cmd)
{
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i, cmd);
	free(exec.cpid);
	free_char_tab_ret(exec);
	free_tab(exec.fd, exec.comm_i);
	return (-1);
}

//	cd -
//	cmd <     ou     cmd |

int	exec_main(t_commands *commands, int nb_comm, t_envlist **envc)
{
	t_exec		exec;
	static int	oldp_stat = 0;

	if (nb_comm < 1)
		return (-1);
	if (nb_comm == 1)
		if (check_cmd_fd(commands[0]) == -1)
			return (-1);
//	if (check_access(commands, nb_comm, envc) == -1)
//		return (-1);
	if (get_tmp_env(envc, &exec) == -1)
		return (free_char_tab_ret(exec));
	if (exec_init(&exec, nb_comm) == -1)
		return (free_char_tab_ret(exec));
	//int	i = 0;
	if (nb_comm == 1)
		is_builtins(commands[exec.comm_i], &exec, envc, &oldp_stat);
	(*envc)->env_ = 1;
	while (exec.temp > 0 && (nb_comm > 1
			|| is_it_builtin(commands[exec.comm_i].sgl_cmd[0], &exec) != 1))
	{
		if (exec.temp > 1)
			if (pipe(exec.fd[exec.comm_i]) == -1)
				return (pipe_error_case(nb_comm, exec, commands));
		exec.cpid[exec.comm_i] = fork();
		if (exec.cpid[exec.comm_i] == 0)
			child_process(commands, &exec, envc, &oldp_stat);
		exec.comm_i++;
		exec.temp--;
	}
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i - 1, commands);
	free_char_tab_ret(exec);
	wait_all_cpid(exec.cpid, exec.status, exec.comm_i, &exec);
	dprintf(1, "%d\n", g_errno);
	free_all(exec, nb_comm);
	return (0);
}