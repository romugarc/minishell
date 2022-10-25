/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:35:01 by rgarcia           #+#    #+#             */
/*   Updated: 2021/11/23 10:59:11 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cpy;

	if (alst)
	{
		if (*alst)
		{
			cpy = ft_lstlast(*alst);
			cpy->next = new;
		}
		else
			*alst = new;
	}
	else
		alst = &new;
}
