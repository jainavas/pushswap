/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_op2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:11:27 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/30 16:44:55 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ra_op(t_psstack **stacka, int both)
{
	t_psstack	*tmp;
	t_psstack	*last;

	if (stacksize(*stacka) <= 1)
		return (0);
	tmp = *stacka;
	*stacka = (*stacka)->next;
	(*stacka)->prev = NULL;
	last = stacklast(*stacka);
	tmp->prev = last;
	tmp->next = NULL;
	last->next = tmp;
	if (both == 0)
		return (op_print(1), 1);
	return (1);
}

int	rb_op(t_psstack **stackb, int both)
{
	t_psstack	*tmp;
	t_psstack	*last;

	if (stacksize(*stackb) <= 1)
		return (0);
	tmp = *stackb;
	*stackb = (*stackb)->next;
	(*stackb)->prev = NULL;
	last = stacklast(*stackb);
	tmp->prev = last;
	tmp->next = NULL;
	last->next = tmp;
	if (both == 0)
		return (op_print(2), 1);
	return (1);
}

int	rr_op(t_psstack **stacka, t_psstack **stackb)
{
	int	i;

	i = 0;
	if (ra_op(stacka, 1) == 1 && rb_op(stackb, 1) == 1)
		i++;
	return (op_print(3), 1);
}

int	rra_op(t_psstack **stacka, int both)
{
	t_psstack	*last;
	t_psstack	*prev_last;

	if (!(*stacka) || !(*stacka)->next)
		return (0);
	last = stacklast(*stacka);
	prev_last = last->prev;
	if (*stacka)
	{
		last->prev = NULL;
		last->next = *stacka;
		last->next->prev = last;
		prev_last->next = NULL;
		*stacka = last;
	}
	if (both == 0)
		return (op_print(4), 1);
	return (1);
}

int	rrb_op(t_psstack **stackb, int both)
{
	t_psstack	*last;
	t_psstack	*prev_last;

	if (!(*stackb) || !(*stackb)->next)
		return (0);
	last = stacklast(*stackb);
	prev_last = last->prev;
	if (*stackb)
	{
		last->prev = NULL;
		last->next = *stackb;
		last->next->prev = last;
		prev_last->next = NULL;
		*stackb = last;
	}
	if (both == 0)
		return (op_print(5), 1);
	return (1);
}
