/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:15 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/27 15:59:30 by fsariogl         ###   ########.fr       */
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
			|| strcmp_tof(var, "_") == 1))
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc)
{
	int	line;

	line = 1;
	while (sgl_cmd[line])
	{
		if (valid_id(sgl_cmd[line], "unset") == 1 && strcmp_tof(sgl_cmd[line], "_") == 0)
			rm_var(sgl_cmd[line], envc);
		line++;
	}
	if (nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}