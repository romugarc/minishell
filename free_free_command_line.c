/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_command_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:04 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/26 17:13:59 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_line(t_commands *commands, char *line, int nb_pipes)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_pipes)
	{
		j = 0;
		while (commands[i].single_command[j] != 0)
		{
			free(commands[i].single_command[j]);
			j++;
		}
		free(commands[i].single_command);
		i++;
	}
	free (commands);
	free (line);
}
