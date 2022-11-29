/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:14:53 by fsariogl          #+#    #+#             */
/*   Updated: 2022/11/27 17:31:54 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **cmds, int nb_comm, t_envlist *envc)
{
	t_envlist	*tmp;

	tmp = envc;
	if (cmds[1])
	{
		printf("env: %s: No such file or directory\n", cmds[1]);
		return (0);
	}
	while (tmp)
	{
		if (tmp->equal == 1)
		{
			printf("%s=", tmp->var);
			if (tmp->val)
				printf("%s\n", tmp->val);
			else
				printf("\n");
		}
		tmp = tmp->next;
	}
	if (nb_comm > 1)
		exit(EXIT_SUCCESS);
	return (0);
}