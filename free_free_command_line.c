/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_command_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:04 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/29 16:54:49 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_line(t_commands *commands, char *line, int nb_pipes)
{
	int	i;

	i = -1;
	if (commands != NULL)
	{
		while (++i < nb_pipes)
		{
			ft_free_tab(commands[i].sgl_cmd);
			if (commands[i].nb_infile > 0)
			{
				free(commands[i].flag_in);
				close_tab_fd(commands[i].tab_fdin, commands[i].nb_infile);
				free(commands[i].tab_fdin);
				ft_free_tab(commands[i].tab_infile);
				if (commands[i].nb_hd > 0)
					ft_free_tab(commands[i].tab_hd);
			}
			if (commands[i].nb_outfile > 0)
			{
				free(commands[i].flag_out);
				close_tab_fd(commands[i].tab_fdout, commands[i].nb_outfile);
				free(commands[i].tab_fdout);
				ft_free_tab(commands[i].tab_outfile);
			}
		}
	}
	free (commands);
	free (line);
}
