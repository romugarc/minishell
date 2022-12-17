/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:07:01 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/08 17:41:45 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int nb_comm, t_cmd cmd, t_exec exec)
{
	char	*path;
	int		out;

	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_putstr_fd(path, out);
		ft_putchar_fd('\n', out);
	}
	free(path);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
