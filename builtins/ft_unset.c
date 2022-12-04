/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:15 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/04 15:23:28 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envlist(t_envlist *envc)
{
	free(envc->var);
	if (envc->val)
		free(envc->val);
	free(envc);
}

void	rm_var(char *var, t_envlist **envc)
{
	t_envlist *cpy;
	t_envlist *sec_cpy;

	if (!(*envc))
		return ;
	cpy = (*envc);
	if (strcmp_tof(var, cpy->var) == 1)
	{
		sec_cpy = cpy->next;
		free_envlist(cpy);
		cpy = sec_cpy;
		(*envc) = cpy;
	}
	if (!cpy->next)
		return ;
	sec_cpy = NULL;
	while (cpy->next)
	{
		if (strcmp_tof(var, cpy->next->var) == 1)
		{
			if (cpy->next->next)
				sec_cpy = cpy->next->next;
			free_envlist(cpy->next);
			if (sec_cpy)
				cpy->next = sec_cpy;
			else
				cpy->next = NULL;
		}
		if (cpy->next)
			cpy = cpy->next;
	}
}

int	valid_id(char *var, char *cmd)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!((var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && var[i] <= 'z')
			|| var[i] == '_'))
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, var);
			return (0);
		}
		i++;
	}
	return (1);
}

void	rm_val(char *str, t_envlist **envc, int *first_time)
{
	t_envlist *cpy;

	cpy = (*envc);
	while (cpy)
	{
		if (strcmp_tof(str, cpy->var) == 1)
		{
			free(cpy->val);
			cpy->val = malloc(sizeof(char));
			if (!cpy->val)
				return ;
			cpy->val[0] = '\0';
			if ((*first_time) == 1)
			{
				cpy->equal = 0;
				(*first_time) = 0;
			}
			break;
		}
		cpy = cpy->next;
	}
}

int	ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc, int *oldp_stat)
{
	int	line;
	int	for_rm_val;

	line = 1;
	for_rm_val = 0;
	while (sgl_cmd[line])
	{
		if (valid_id(sgl_cmd[line], "unset") == 1 && strcmp_tof(sgl_cmd[line], "_") == 0)
		{
			if (strcmp_tof(sgl_cmd[line], "PWD") != 1)
				rm_var(sgl_cmd[line], envc);
			else if (strcmp_tof(sgl_cmd[line], "PWD") == 1)
			{
				(*oldp_stat) = -1;
				rm_val(sgl_cmd[line], envc, &for_rm_val);
			}
		}
		line++;
	}
	if (nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}