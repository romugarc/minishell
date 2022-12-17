/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:14:53 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 20:46:47 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_line_tiret(t_cmd cmd)
{
	int	i;

	if (cmd.sgl_cmd[1])
	{
		i = 0;
		if (cmd.sgl_cmd[1][0] == '-')
		{
			while (cmd.sgl_cmd[1][i] == '-' && cmd.sgl_cmd[1][i])
				i++;
			if (cmd.sgl_cmd[1][i] == '\0')
			{
				g_errno = 0;
				return (2);
			}
			return (put_char_error(cmd.sgl_cmd[1][i], 1, 0));
		}
		return (put_char_error(cmd.sgl_cmd[1][i], 1, 0));
	}
	return (0);
}

static void	display_env(t_envlist *tmp, int oldp_stat, int out)
{
	while (tmp)
	{
		if (strcmp_tof(tmp->var, "PWD") == 1 && oldp_stat == -1)
			tmp = tmp->next;
		if (tmp->equal == 1)
		{
			ft_putstr_fd(tmp->var, out);
			ft_putchar_fd('=', out);
			if (tmp->val)
			{
				ft_putstr_fd(tmp->val, out);
				ft_putchar_fd('\n', out);
			}
			else
				ft_putchar_fd('\n', out);
		}
		tmp = tmp->next;
	}
}

int	ft_env(t_cmd cmd, t_exec exec, t_envlist *envc, int oldp_stat)
{
	int			ret;
	int			out;
	t_envlist	*tmp;

	tmp = envc;
	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
	ret = check_line_tiret(cmd);
	if (ret == 2)
		return (0);
	else if (ret == -1)
		return (-1);
	display_env(tmp, oldp_stat, out);
	g_errno = 0;
	if (exec.nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}
