/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:42:55 by fsariogl          #+#    #+#             */
/*   Updated: 2022/12/16 20:26:45 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_char_tab_ret(t_exec exec)
{
	int	i;

	i = 0;
	if (!exec.env_tmp)
		return (-1);
	while (exec.env_tmp[i])
		free(exec.env_tmp[i++]);
	if (exec.env_tmp)
		free(exec.env_tmp);
	return (-1);
}

void	ft_strjoin_env_next(t_exec *exec, t_envlist **tmp, t_inc *inc)
{
	(*inc).n = 0;
	(*inc).i = 0;
	while ((*tmp)->var[(*inc).i])
		exec->env_tmp[(*inc).l_i][(*inc).n++] = (*tmp)->var[(*inc).i++];
	if ((*tmp)->equal == 1)
		exec->env_tmp[(*inc).l_i][(*inc).n++] = '=';
	(*inc).i = 0;
	while ((*tmp)->val[(*inc).i])
		exec->env_tmp[(*inc).l_i][(*inc).n++] = (*tmp)->val[(*inc).i++];
	exec->env_tmp[(*inc).l_i][(*inc).n] = '\0';
	(*tmp) = (*tmp)->next;
	(*inc).l_i++;
}

int	ft_strjoin_env(t_envlist **envc, t_exec *exec)
{
	t_inc		inc;
	t_envlist	*tmp;

	tmp = (*envc);
	init_inc(&inc);
	while (tmp != NULL)
	{
		inc.n = 0;
		inc.j = 0;
		while (tmp->var && tmp->var[inc.n])
			inc.n++;
		inc.n = inc.n + tmp->equal;
		while (tmp->val && tmp->val[inc.j])
			inc.j++;
		inc.n = inc.n + inc.j;
		exec->env_tmp[inc.l_i] = malloc(sizeof(char) * (inc.n + 1));
		if (!exec->env_tmp[inc.l_i])
			return (mall_error());
		ft_strjoin_env_next(exec, &tmp, &inc);
	}
	exec->env_tmp[inc.l_i] = NULL;
	return (0);
}

int	get_tmp_env(t_envlist **envc, t_exec *exec)
{
	int			size;
	t_envlist	*tmp;

	size = 0;
	tmp = (*envc);
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	exec->env_tmp = malloc(sizeof(char *) * (size + 1));
	if (!exec->env_tmp)
		return (mall_error());
	return (ft_strjoin_env(envc, exec));
}
