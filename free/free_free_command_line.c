/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_command_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:04 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:37:52 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_taboutfile(t_cmd *commands, int i)
{
	free(commands[i].flag_out);
	close_tab_fd(commands[i].tab_fdout, commands[i].nb_outf);
	free(commands[i].tab_fdout);
	ft_free_tab(commands[i].tab_outf);
}

static void	free_tabinfile(t_cmd *commands, int i)
{
	free(commands[i].flag_in);
	close_tab_fd(commands[i].tab_fdin, commands[i].nb_inf);
	free(commands[i].tab_fdin);
	ft_free_tab(commands[i].tab_inf);
}

void	free_command_line(t_cmd *commands, char *line, int nb_pipes, int g)
{
	int	i;

	i = -1;
	if (commands != NULL)
	{
		while (++i < nb_pipes)
		{
			ft_free_tab(commands[i].sgl_cmd);
			if (commands[i].nb_inf > 0 && g != 258)
				free_tabinfile(commands, i);
			if (commands[i].nb_outf > 0 && g != 258)
				free_taboutfile(commands, i);
		}
	}
	free (commands);
	free (line);
}
