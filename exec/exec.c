/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:13:18 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/16 15:15:57 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free_tab(exec.fd, exec.comm_i);
	return (1);
}

int	exec_main(t_commands *commands, int nb_comm, char **envp)
{
	t_exec		exec;

//	commands = check_access(commands);
	if (exec_init(&exec, commands, nb_comm, envp) == 1)
		return (1);
	if (nb_comm == 1)
		is_builtins(commands[exec.comm_i].single_command, nb_comm);
	while (exec.temp > 0 && (nb_comm > 1
			|| is_it_builtin(commands[0].single_command[0]) != 1))
	{
		if (exec.temp > 1)
			if (pipe(exec.fd[exec.comm_i]) == -1)
				return (pipe_error_case(nb_comm, exec));
		exec.cpid[exec.comm_i] = fork();
		if (exec.cpid[exec.comm_i] == 0)
			child_process(commands, exec, nb_comm);
		exec.comm_i++;
		exec.temp--;
	}
	if (nb_comm > 1)
		close_fd(exec.fd, exec.comm_i - 1);
	wait_all_cpid(exec.cpid, exec.status, exec.comm_i);
	free_all(exec, nb_comm);
	return (0);
}
