/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_command_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:04 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/26 16:46:23 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_line(t_commands *commands, char *line, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		ft_free_tab(commands[i].sgl_cmd);
		if (commands[i].nb_infile > 0)
			free(commands[i].flag_in);
		if (commands[i].nb_infile > 0)
			ft_free_tab(commands[i].tab_infile);
		if (commands[i].nb_outfile > 0)
			free(commands[i].flag_out);
		if (commands[i].nb_outfile > 0)
			ft_free_tab(commands[i].tab_outfile);
		i++;
	}
	free (commands);
	free (line);
}
