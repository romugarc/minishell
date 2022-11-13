/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:07:01 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/13 14:57:53 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int nb_comm)
{
	char	*path;

	path = malloc(sizeof(char) * 10000000);
	if (!path)
		return (-1);
	path = getcwd(path, 10000000);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	if (nb_comm != 1)
		exit(EXIT_SUCCESS);
	return (1);
}
