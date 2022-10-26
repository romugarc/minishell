#include "minishell.h"
#include <sys/wait.h>

int	main(void)
{
	int			status;
	pid_t 		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (commands[0].single_command != 0)
			execve(commands[0].single_command[0], commands[0].single_command, envp);
	}
	else
		wait(&status);
	return (0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
