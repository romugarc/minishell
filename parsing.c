/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/31 17:45:26 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(flag_string, *line) != 0)
		return (1);
	if (quotes_flags(flag_string, *line) != 0)
		return (1);
	*nb_pipes = count_arguments(*line, '|', *flag_string);
	*commands = init_commands(*line, *nb_pipes, *flag_string);
	return (0);
}
