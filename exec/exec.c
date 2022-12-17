/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 19:01:01 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	pipe_error_case(int nb_comm, t_exec exec, t_cmd *cmd)
{
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i, cmd);
	free(exec.cpid);
	free_char_tab_ret(exec);
	free_tab(exec.fd, exec.comm_i);
	return (-1);
}

int	exec_error_case(t_cmd *cmd, t_envlist **envc, t_exec *exec, int *oldp)
{
	if (!cmd)
		return (-1);
	if ((*exec).nb_comm == 1)
	{
		if ((check_cmd_fd(cmd[0]) == -1
				|| check_access(cmd[0], envc) == -1) || !cmd)
		{
			return (free_char_tab_ret(*exec));
		}
	}
	if (get_tmp_env(envc, exec) == -1)
		return (free_char_tab_ret(*exec));
	if (exec_init(exec) == -1)
		return (free_char_tab_ret(*exec));
	if ((*exec).nb_comm == 1)
		is_builtins(cmd[(*exec).comm_i], exec, envc, oldp);
	if ((*envc))
		(*envc)->env_ = 1;
	return (0);
}

int	pipe_exec(t_exec *exec, t_cmd *cmd, t_envlist **envc, int *oldp_stat)
{
	if ((*exec).temp > 1)
		if (pipe((*exec).fd[(*exec).comm_i]) == -1)
			return (pipe_error_case((*exec).nb_comm, (*exec), cmd));
	if (strcmp_tof(cmd[0].sgl_cmd[0], "./minishell") != 1)
	{
		signal(SIGINT, pipe_sighandler);
		signal(SIGQUIT, pipe_sighandler);
	}
	else
	{
		signal(SIGINT, cancel_sighandler);
		signal(SIGQUIT, cancel_sighandler);
	}
	(*exec).cpid[(*exec).comm_i] = fork();
	if ((*exec).cpid[(*exec).comm_i] == 0)
		child_process(cmd, exec, envc, oldp_stat);
	(*exec).comm_i++;
	(*exec).temp--;
	return (0);
}

int	exec_main(t_cmd *commands, int nb_comm, t_envlist **envc)
{
	t_exec		exec;
	static int	oldp_stat = 0;

	exec.temp = nb_comm;
	if (nb_comm < 1)
		return (-1);
	if (nb_comm == 1)
		if (!commands[0].sgl_cmd[0])
			return (-1);
	if (exec_error_case(commands, envc, &exec, &oldp_stat) == -1)
		return (-1);
	while (exec.temp > 0 && (nb_comm > 1
			|| is_it_builtin(commands[exec.comm_i].sgl_cmd[0], &exec) != 1))
	{
		if (pipe_exec(&exec, commands, envc, &oldp_stat) == -1)
			return (-1);
	}
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i - 1, commands);
	free_char_tab_ret(exec);
	wait_all_cpid(exec.cpid, exec.status, exec.comm_i, &exec);
	free_all(exec, nb_comm);
	return (0);
}
