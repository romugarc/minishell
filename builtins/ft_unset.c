/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:15 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/17 17:05:13 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_id(char *var, char *cmd)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isenvarc(var[0], 1) == 0 || ft_isenvarc(var[i], 0) == 0)
			return (puterror(cmd, var, 3, 0));
		i++;
	}
	return (1);
}

int	rm_val(char *str, t_envlist **envc, int *first_time)
{
	t_envlist	*cpy;

	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(str, cpy->var) == 1)
		{
			free(cpy->val);
			cpy->val = malloc(sizeof(char));
			if (!cpy->val)
				return (-1);
			cpy->val[0] = '\0';
			if ((*first_time) == 1)
			{
				cpy->equal = 0;
				(*first_time) = 0;
			}
			break ;
		}
		cpy = cpy->next;
	}
	return (0);
}

int	init_vars(int *line, int *for_rm_val, char *sglcmdline, int mode)
{
	int	ret;

	if (mode == 0)
	{
		*line = 1;
		*for_rm_val = 0;
		g_errno = 0;
	}
	else if (mode == 1)
	{
		ret = valid_id(sglcmdline, "unset");
		if (g_errno == 0 && ret == 0)
			g_errno = 1;
		return (ret);
	}
	return (0);
}

int	exit_or_rmvar(int nb_comm, t_envlist **envc, char *sglcmdline, int mode)
{
	if (mode == 0)
	{
		g_errno = 134;
		if (nb_comm > 1)
			exit(EXIT_FAILURE);
		return (-1);
	}
	else if (mode == 1)
	{
		if (nb_comm > 1)
			exit(EXIT_SUCCESS);
		if ((*envc))
			(*envc)->env_ = 1;
	}
	else if (mode == 2)
	{
		if (strcmp_tof(sglcmdline, "PWD") != 1)
			rm_var(sglcmdline, envc);
	}
	return (0);
}

int	ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc, int *oldp)
{
	int	ret;
	int	line;
	int	for_rm_val;

	line = 0;
	for_rm_val = 0;
	init_vars(&line, &for_rm_val, sgl_cmd[line], 0);
	while (sgl_cmd[line])
	{
		ret = init_vars(&line, &for_rm_val, sgl_cmd[line], 1);
		if (strcmp_tof(sgl_cmd[line], "_") == 0 && ret == 1)
		{
			exit_or_rmvar(nb_comm, envc, sgl_cmd[line], 2);
			if (strcmp_tof(sgl_cmd[line], "PWD") == 1)
			{
				(*oldp) = -1;
				if (rm_val(sgl_cmd[line], envc, &for_rm_val) == -1)
					if (exit_or_rmvar(nb_comm, envc, sgl_cmd[line], 0) == -1)
						return (-1);
			}
		}
		line++;
	}
	exit_or_rmvar(nb_comm, envc, sgl_cmd[line], 1);
	return (0);
}
