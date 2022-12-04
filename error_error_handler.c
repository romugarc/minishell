/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:40:16 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/02 19:14:58 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(int argc, char **argv)
{
	(void) argv;
	if (argc > 1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	return (0);
}
