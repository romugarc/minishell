/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/30 15:55:35 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	*nb_pipes = count_arguments(*line, '|');
	if (special_char_flags(flag_string, *line) != 0)
		return (1);
	if (quotes_flags(flag_string, *line) != 0)
		return (1);
	*commands = init_commands(*line, *nb_pipes);
	return (0);
}
