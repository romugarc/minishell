/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init_command_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:08:45 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/28 19:06:01 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command_tab(t_commands **commands, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		(*commands)[i].tab_infile = NULL;
		(*commands)[i].tab_outfile = NULL;
		(*commands)[i].tab_heredoc = NULL;
		(*commands)[i].flag_in = NULL;
		(*commands)[i].flag_out = NULL;
		(*commands)[i].tab_fdin = NULL;
		(*commands)[i].tab_fdout = NULL;
		i++;
	}
}
