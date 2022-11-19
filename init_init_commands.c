/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:22:01 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/19 15:06:51 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*init_commands(char	*line, int nb_pipes, t_f_str *fs)
{
	int			i;
	t_commands	*commands;
	char		**full_command_line;

	full_command_line = ft_split_v2old(line, '|', *fs);
	commands = malloc(sizeof(t_commands) * nb_pipes);
	if (!commands)
		return (0);
	i = 0;
	while (full_command_line[i] != 0)
	{
		commands[i].sgl_cmd = ft_split_v2(full_command_line[i], ' ', fs);
		while (fs->sp_chars[fs->i.k] == '5' && fs->quotes[fs->i.k] == '0')
		{
			fs->i.i += 1;
			fs->i.k += 1;
		}
		i++;
	}
	i = 0;
	while (i < nb_pipes)
	{
		free(full_command_line[i]);
		i++;
	}
	free(full_command_line);
	return (commands);
}
