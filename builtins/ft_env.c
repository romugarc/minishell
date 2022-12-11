/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:14:53 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/11 11:32:01 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_commands cmd, t_exec exec, t_envlist *envc, int oldp_stat)
{
	int			i;
	int			out;
	t_envlist	*tmp;

	tmp = envc;
	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
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
				return (0);
			}
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(cmd.sgl_cmd[1][i], 2);
			ft_putchar_fd('\n', 2);
			g_errno = 1;
			return (0);
		}
		ft_putstr_fd("env: ", 2);
		ft_putchar_fd(cmd.sgl_cmd[1][1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_errno = 127;
		return (0);
	}
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
	g_errno = 0;
	if (exec.nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}