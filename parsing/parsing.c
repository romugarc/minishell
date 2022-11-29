/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/29 16:56:38 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_commands **commands, t_f_str *f_str, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(f_str, *line) != 0)
		return (1);
	if (quotes_flags(f_str, *line) != 0)
		return (1);
	init_inc(&f_str->i);
	*nb_pipes = count_arguments(*line, '|', f_str);
	f_str->i.k = 0;
	*commands = init_commands(*line, *nb_pipes, f_str);
	init_command_tab(commands, *nb_pipes);
	count_redirections(commands, *nb_pipes, *f_str);
	// parcourir commands[i].nb_infiles et outfiles et si ces valeurs sont à 0, on ne fait pas les 2 prochaines lignes
	if(malloc_tab_files(commands, *nb_pipes) == 1)
		return (1);
	if (form_tab(commands, *f_str, *nb_pipes) == 1)
		return (1);
	if (form_tab2(commands, *f_str, *nb_pipes) == 1)
		return (1);
	correct_tab(commands, *f_str, *nb_pipes);
	if (reform_tab(commands, *nb_pipes) == 1)
		return (1);
	if (form_heredoc(commands, *nb_pipes) == 1)
		return (1);
	if (create_fd(commands, *nb_pipes) == 1)
		return (1);
	return (0);
}

//debug code pour commands (attention aux segfault si y a rien dans commands)
/*	i = 0;
	while (i < *nb_pipes)
	{
		printf("avantnb\n");
		commands[i]->nb_infile = 0;
		commands[i]->nb_outfile = 0;
		printf("avantredir\n");
		count_redirections(commands[i], *flag_string, tab);
		printf("%d\t%d\n", commands[i]->nb_infile, commands[i]->nb_outfile);
		i++;
	}*/
/*	i = 0;
	while (i < *nb_pipes)
	{
		j = 0;
		while ((*commands)[i].sgl_cmd[j] != 0)
		{
			printf("%s.%d\n", (*commands)[i].sgl_cmd[j], i);
			j++;
		}
		j = 0;
		while ((*commands)[i].nb_infile > 0 && j < (*commands)[i].nb_infile)
		{
			printf("%s.%d.infile\n", (*commands)[i].tab_infile[j], i);
			j++;
		}
		if ((*commands)[i].nb_infile > 0)
			printf("%s.%dfin\n", (*commands)[i].flag_in, i);
		j = 0;
		while ((*commands)[i].nb_outfile > 0 && j < (*commands)[i].nb_outfile)
		{
			printf("%s.%d.outfile\n", (*commands)[i].tab_outfile[j], i);
			j++;
		}
		if ((*commands)[i].nb_outfile > 0)
			printf("%s.%dfout\n", (*commands)[i].flag_out, i);
		i++;
	}*/
