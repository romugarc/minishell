/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:22:01 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:37:46 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_full_command_line(char **fcl, int nbp)
{
	int	i;

	i = 0;
	while (i < nbp)
	{
		free(fcl[i]);
		i++;
	}
	free(fcl);
}

t_cmd	*init_commands(char	*line, int nb_pipes, t_f_str *fs)
{
	int		i;
	t_cmd	*commands;
	char	**full_command_line;

	full_command_line = ft_split_v2old(line, '|', *fs);
	commands = malloc(sizeof(t_cmd) * (nb_pipes + 1));
	if (!commands)
		return (NULL);
	i = 0;
	while (full_command_line[i] != 0)
	{
		commands[i].sgl_cmd = ft_split_v2(full_command_line[i], ' ', fs);
		if (!commands[i].sgl_cmd)
			return (NULL);
		while (fs->sp_chars[fs->i.k] == '5' && fs->quotes[fs->i.k] == '0')
		{
			fs->i.i += 1;
			fs->i.k += 1;
		}
		i++;
	}
	commands[i].sgl_cmd = NULL;
	free_full_command_line(full_command_line, nb_pipes);
	return (commands);
}
