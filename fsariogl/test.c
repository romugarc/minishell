#include "minishell.h"
#include <sys/wait.h>

//int	main(void)
//{
//	int			status;
//	pid_t 		pid;
//
//	pid = fork();
//	if (pid == -1)
//	{
//		perror("fork");
//		exit(EXIT_FAILURE);
//	}
//	else if (pid == 0)
//	{
//		if (commands[0].single_command != 0)
//			execve(commands[0].single_command[0], commands[0].single_command, envp);
//	}
//	else
//		wait(&status);
//	return (0);
//}
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//int	strlen_until(char *str, char *until)
//{
//	int	i;
//	int	u;
//
//	i = 0;
//	while (str[i])
//	{
//		u = 0;
//		while (until[u])
//		{
//			if (str[i] == until[u])
//				return (i);
//			u++;
//		}
//		i++;
//	}
//	return (i);
//}

//
//int	strlen_from(char *str, char *from)
//{
//	int	i;
//	int	f;
//	int	count;
//
//	i = 0;
//	count = -2;
//	while (str[i])
//	{
//		f = 0;
//		while (from[f])
//			if (str[i] == from[f++] && count == -2)
//				count = -1;
//		i++;
//		if (count >= -1)
//			count++;
//	}
//	return (count);
//}
//
//
//int	main(int ac, char **av, char **envp)
//{
//	char	*str = "Bonjour, comment";
//
//	printf("%d\n", strlen_from("49TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000bst8002yfk/T/dsadsa", "="));
//	return (0);
//}




int	main(void)
{
	int	value;
	char	*s;

	while (1)
		s = malloc(sizeof(char) * 100000);
	value = access("/bn/ls", X_OK | F_OK);
	printf("EACCES = %d, ELOOP = %d, ENAMETOOLONG = %d, ENOENT = %d, ENOTDIR = %d, EROFS = %d\n", EACCES, ELOOP, ENAMETOOLONG, ENOENT, ENOTDIR, EROFS);
	printf("EFAULT = %d, EINVAL = %d, EIO = %d, ENOMEM = %d, ETXTBSY = %d\n", EFAULT, EINVAL, EIO, ENOMEM, ETXTBSY);
	printf("%d -- %d\n", errno, value);
	return (0);
}