/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:06:54 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 13:22:50 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_next(t_cmd cmd, t_envlist **envc, int *oldp_stat)
{
	int	i;
	int	ret;

	i = 1;
	while (cmd.sgl_cmd[i])
	{
		ret = valid_id_exp(cmd.sgl_cmd[i], "export", oldp_stat);
		if (ret == 0)
			g_errno = 1;
		if (ret == 1)
			if (add_export(envc, cmd.sgl_cmd[i], '=') == -1)
				return (mall_error());
		if (ret == 2)
			add_export(envc, cmd.sgl_cmd[i], '+');
		i++;
	}
	return (0);
}

int	ft_export(t_cmd cmd, t_exec exec, t_envlist **envc, int *oldp_stat)
{
	int		out;

	g_errno = 0;
	if (exec.nb_comm == 1)
		out = cmd.fdout;
	else
		out = 1;
	if (!cmd.sgl_cmd)
		return (-1);
	if (!cmd.sgl_cmd[1])
		print_export((*envc), (*oldp_stat), out);
	else
		if (ft_export_next(cmd, envc, oldp_stat) == -1)
			return (-1);
	if (exec.nb_comm > 1)
		exit(EXIT_SUCCESS);
	if ((*envc))
		(*envc)->env_ = 1;
	return (0);
}
