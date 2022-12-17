/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 14:22:57 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freeing_all(t_misc misc, t_envlist *envc)
{
	free(misc.line);
	free_envc(envc);
	rl_clear_history();
}

static int	form_line(t_misc *m, t_f_str *f_str, t_envlist *envc)
{
	if (m->line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		freeing_all(*m, envc);
		exit(EXIT_SUCCESS);
	}
	if (m->line[0] != '\0')
		add_history(m->line);
	if (special_char_flags(f_str, m->line) != 0)
		return (134);
	if (quotes_flags(f_str, m->line) != 0)
		return (134);
	return (0);
}

static int	v_p(t_cmd **commands, t_misc *m, t_envlist *en)
{
	if (malloc_tab_files(commands, m->nb_commands) == 1)
		return (134);
	if (form_tab(commands, m->nb_commands) == 1)
		return (134);
	if (form_tab2(commands, m->nb_commands) == 1)
		return (134);
	correct_tab(commands, m->nb_commands);
	if (reform_tab(commands, m->nb_commands) == 1)
		return (134);
	if (expand_variable(commands, m->nb_commands, en) == 1)
		return (134);
	if (remove_quotes(commands, m->nb_commands) == 1)
		return (134);
	if (create_fd(commands, m->nb_commands, en) == 134)
		return (134);
	if (g_errno == -42)
		return (1);
	check_fd(commands, m->nb_commands);
	return (0);
}

int	parsing(t_cmd **cmd, t_f_str *f_str, t_misc *m, t_envlist *envc)
{
	int	ret;

	m->line = readline("minishell$ ");
	if (form_line(m, f_str, envc) == 134)
		return (134);
	ret = parse_error(m->line, *f_str);
	init_inc(&f_str->i);
	m->nb_commands = count_arguments(m->line, '|', f_str);
	f_str->i.k = 0;
	*cmd = init_commands(m->line, m->nb_commands, f_str);
	if (*cmd == NULL)
		return (134);
	init_command_tab(cmd, m->nb_commands);
	count_redirections(cmd, m->nb_commands, *f_str);
	if (ret != 0)
		return (258);
	else
	{
		ret = v_p(cmd, m, envc);
		if (ret == 1)
			return (1);
		else if (ret == 134)
			return (134);
	}
	return (0);
}
