/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/22 19:27:27 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int	tab_redirections(t_commands **commands, t_flag_string flag_string, char **line)
{
	
	return (0);
}*/
/*int	split_redirection(char *tab, char **tab_files, int nb_files, t_flag_string f_str)
{
	int	i;
	int	j;

	i = 0;
	(void)f_str;
	while (tab_files[i] != 0)
		i++;
	while (i < nb_files)
	{
		j = 0;
		while (tab[j] != '\0')
		{
			j++;
		}
		i++;
	}
	return (0);
}*/

/*char	*form_tab_2(char c, t_commands *comm, t_flag_string f_str, t_inc *inc)
{
	int		start;
	int		end;
	char	*ret;

	printf("%s\n", f_str.special_chars);
	start = find_special_char(c, f_str, &inc->k);
	while ((f_str.special_chars[inc->k] == c || f_str.special_chars[inc->k] == '9') && f_str.special_chars[inc->k] != '\0')
		inc->k++;
	start = inc->k;
	printf("%d\t%c\n", start, f_str.special_chars[start]);
	end = find_end_redirection(f_str, &inc->k);
	printf("%d\t%c\n", end, f_str.special_chars[end]);
	ret = ft_strdup_s_to_e(comm[inc->i].single_command[inc->j], start, end);
	printf("%s\n", comm[inc->i].single_command[inc->j]);
	printf("%s\n", ret);
	inc->n += 1;
	return (ret);
}*/


/*int	form_tab2(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int		start;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_outfile)
		{
			while ((f_str.sp_chars[i.k] == '5' \
					|| f_str.sp_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			start = find_special_char('6', f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
			if (start > -1)
				manage_outfile(com, &f_str, &i, &start);
			if (((*com)[i.i].sgl_cmd[i.j] != 0 && (*com)[i.i].sgl_cmd[i.j][i.l_e] == '\0') || start == -1)
				i.j += 1;
		}
		if ((*com)[i.i].nb_outfile == 0 && f_str.quotes[i.k] != '\0')
			i.k += ft_strlen((*com)[i.i].sgl_cmd[i.j]);
		else if (f_str.quotes[i.k] != '\0')
			i.k += 1;
		i.i += 1;
	}
	return (0);
}

int	form_tab(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int		start;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0 && i.n < (*com)[i.i].nb_infile)
		{
			while ((f_str.sp_chars[i.k] == '5' \
					|| f_str.sp_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			start = find_special_char('7', f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
			if (start > -1)
				manage_infile(com, &f_str, &i, &start);
			if (((*com)[i.i].sgl_cmd[i.j] != 0 && (*com)[i.i].sgl_cmd[i.j][i.l_e] == '\0') || start == -1)
				i.j += 1;
		}
		if ((*com)[i.i].nb_infile == 0 && f_str.quotes[i.k] != '\0')
			i.k += ft_strlen((*com)[i.i].sgl_cmd[i.j]);
		else if (f_str.quotes[i.k] != '\0')
			i.k += 1;
		i.i += 1;
	}
	return (0);
}


int	ft_del_str_from_i(char *str, int i)
{
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	return (0);
}

int	update_k(char *str, int i)
{
	int	k;

	k = i;
	while (str[i] != '\0')
	{
		i++;
		k++;
	}
	return (k);
}

int	find_start_char(t_f_str f_str, t_inc *inc, char *s_c)
{
	int	i;

	if (inc->l_j == inc->j)
		i = inc->l_e;
	else
	{
		inc->l_j = inc->j;
		i = 0;
	}
	while (f_str.sp_chars[inc->k] != '\0' && s_c[i] != '\0')
	{
		if ((f_str.sp_chars[inc->k] == '7' || f_str.sp_chars[inc->k] == '6') \
			&& f_str.quotes[inc->k] == '0')
		{
				inc->l_i = i;
				return (i);
		}
		inc->k += 1;
		i++;
	}
	inc->l_i = 0;
	return (-1);
}

int	set_del_flag(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '\0')
		return (1);
	else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
		return (1);
	return (0);
}

int	correct_tab(t_commands **com, t_f_str f_str, int np)
{
	t_inc	i;
	int		start;
	int		del_flag;

	i.i = 0;
	i.k = 0;
	while(i.i < np)
	{
		i.n = 0;
		i.l_i = 0;
		i.l_j = 0;
		i.l_e = 0;
		i.j = 0;
		del_flag = 0;
		while ((*com)[i.i].sgl_cmd[i.j] != 0)
		{
			while ((f_str.sp_chars[i.k] == '5' \
					|| f_str.sp_chars[i.k] == '9') \
					&& f_str.quotes[i.k] == '0')
				i.k += 1;
			start = find_start_char(f_str, &i, (*com)[i.i].sgl_cmd[i.j]);
			if (start > -1 || del_flag == 1)
			{
				if (del_flag == 0)
					del_flag = set_del_flag((*com)[i.i].sgl_cmd[i.j]);
				else
				{
					start = 0;
					del_flag = 0;
				}
				i.k = update_k((*com)[i.i].sgl_cmd[i.j], start);
				i.l_e = i.k;
				ft_del_str_from_i((*com)[i.i].sgl_cmd[i.j], start);
			}
			if (((*com)[i.i].sgl_cmd[i.j] != 0 && (*com)[i.i].sgl_cmd[i.j][i.l_e] == '\0') || start == -1)
				i.j += 1;
		}
		if (f_str.quotes[i.k] != '\0')
			i.k += 1;
		i.i += 1;
	}
	return (0);
}*/

/*int	correct_tabs(t_commands **c, t_flag_string flag_string, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if ((*c)[i].nb_infile > 0)
		{
			form_tab(&(*c)[i], flag_string);
		}
		if ((*c)[i].nb_outfile > 0)
		{
			(*c)[i].tab_outfile = malloc(sizeof(char *) * (*c)[i].nb_outfile);
			if (!(*c)[i].tab_outfile)
				return (1);
		}
		i++;
	}
	return (0);
}*/

int	parsing(t_commands **commands, t_f_str *f_str, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(f_str, *line) != 0)
		return (1);
	if (quotes_flags(f_str, *line) != 0)
		return (1);
	f_str->i = init_inc(f_str->i);
	*nb_pipes = count_arguments(*line, '|', f_str);
	f_str->i.k = 0;
	*commands = init_commands(*line, *nb_pipes, f_str);
//	count_redirections(commands, *nb_pipes, *f_str);
	// parcourir commands[i].nb_infiles et outfiles et si ces valeurs sont à 0, on ne fait pas les 2 prochaines lignes
//	malloc_tab_files(commands, *nb_pipes);
//	form_tab(commands, *f_str, *nb_pipes);
//	form_tab2(commands, *f_str, *nb_pipes);
//	correct_tab(commands, *f_str, *nb_pipes);
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

