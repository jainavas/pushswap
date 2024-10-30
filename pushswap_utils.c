/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:42:03 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/21 19:42:03 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_psstack	*stacknew(int data)
{
	t_psstack	*new;

	new = ft_calloc(1, sizeof(t_psstack));
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_psstack	*stacklast(t_psstack *lst)
{
	t_psstack	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

t_psstack	*stackfirst(t_psstack *lst)
{
	t_psstack	*tmp;

	tmp = lst;
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

void	stackclear(t_psstack **lst)
{
	t_psstack	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		*lst = aux;
	}
}

void	stackadd_front(t_psstack **lst, t_psstack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
	}
	else
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
	}
}
