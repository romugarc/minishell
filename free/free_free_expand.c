/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_free_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:10:30 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 17:38:00 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_expand(char *a, char *b, char *c, char *d)
{
	if (a != NULL)
		free(a);
	if (b != NULL)
		free(b);
	if (c != NULL)
		free(c);
	if (d != NULL)
		free(d);
	return (1);
}
