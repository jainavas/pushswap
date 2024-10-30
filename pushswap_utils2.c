/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:14:37 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/29 17:53:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	getmaxmin(t_psstack *stackb, t_pscount *ct)
{
	int	i;

	i = 0;
	if (ct->maxb != INT_MIN)
	{
		ct->posmaxb = getindex(stackb, ct->maxb);
		ct->posminb = getindex(stackb, ct->minb);
	}
	while (stackb)
	{
		if (stackb->data > ct->maxb)
		{
			ct->maxb = stackb->data;
			ct->posmaxb = i;
		}
		if (stackb->data < ct->minb)
		{
			ct->minb = stackb->data;
			ct->posminb = i;
		}
		i++;
		stackb = stackb->next;
	}
}

void	stackadd_back(t_psstack **lst, t_psstack *new)
{
	t_psstack	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = stacklast(*lst);
		new->next = NULL;
		tmp->next = new;
		new->prev = tmp;
	}
}

int	stacksize(t_psstack *lst)
{
	t_psstack	*new;
	int			i;

	i = 0;
	new = stackfirst(lst);
	while (new)
	{
		new = new->next;
		i++;
	}
	return (i);
}

int	checkascending(t_psstack *stacka)
{
	while (stacka->next)
	{
		if (stacka->data > stacka->next->data)
			return (stacka->data);
		stacka = stacka->next;
	}
	return (0);
}

void	printstacks(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
	ft_printf("\nContenido a: \n");
	while (stacka)
	{
		ft_printf("%d ", (stacka->data));
		stacka = stacka->next;
	}
	ft_printf("\nContenido b: \n");
	while (stackb)
	{
		ft_printf("%d ", (stackb->data));
		stackb = stackb->next;
	}
	if (ct)
		printf("\nnum ops: %d\n", ct->numop);
}
