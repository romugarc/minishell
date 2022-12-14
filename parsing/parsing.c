/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/13 19:11:55 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_commands **commands, t_f_str *f_str, t_misc *misc, t_envlist *envc)
{
	int	i;
	int	j;
	int	ret;

//	misc->line = get_next_line(0);
//	misc->line = correct_line(misc->line);
	misc->line = readline("minishell$ ");
	add_history(misc->line);
	if (special_char_flags(f_str, misc->line) != 0)
		return (134);
	if (quotes_flags(f_str, misc->line) != 0)
		return (134);
//	if (expand_variablee(&misc->line, envc) == 1)
//		return (134);
	ret = parse_error(misc->line, *f_str);
	init_inc(&f_str->i);
	misc->nb_commands = count_arguments(misc->line, '|', f_str);
	f_str->i.k = 0;
	*commands = init_commands(misc->line, misc->nb_commands, f_str);
	if (*commands == NULL)
		return (134);
	init_command_tab(commands, misc->nb_commands);
	count_redirections(commands, misc->nb_commands, *f_str);
	// parcourir commands[i].nb_infiles et outfiles et si ces valeurs sont à 0, on ne fait pas les 2 prochaines lignes
	if(malloc_tab_files(commands, misc->nb_commands) == 1)
		return (134);
	if (ret == 0)
	{
		if (form_tab(commands, misc->nb_commands) == 1)
			return (134);
		if (form_tab2(commands, misc->nb_commands) == 1)
			return (134);
		correct_tab(commands, misc->nb_commands);
		if (reform_tab(commands, misc->nb_commands) == 1)
			return (134);
		if (expand_variable(commands, misc->nb_commands, envc) == 1)
			return (134);
		if (remove_quotes(commands, misc->nb_commands) == 1)
			return (134);
		if (create_fd(commands, misc->nb_commands, envc) == 134)
			return (134);
		check_fd(commands, misc->nb_commands);
		return (0);
	}
	return (258);
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
