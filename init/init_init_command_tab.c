/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init_command_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:08:45 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:37:43 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_command_tab(t_cmd **commands, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		(*commands)[i].tab_inf = NULL;
		(*commands)[i].tab_outf = NULL;
		(*commands)[i].flag_in = NULL;
		(*commands)[i].flag_out = NULL;
		(*commands)[i].tab_fdin = NULL;
		(*commands)[i].tab_fdout = NULL;
		(*commands)[i].nb_inf = 0;
		(*commands)[i].nb_outf = 0;
		i++;
	}
}
