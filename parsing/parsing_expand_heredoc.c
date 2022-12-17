/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:14:20 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:14:22 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_heredoc(char **str, t_envlist *envc)
{
	if (search_expand(str, envc) == 1)
		return (1);
	return (0);
}
