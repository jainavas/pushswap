/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswapmoves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:04:10 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/28 20:00:00 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	putbigfirst(t_psstack **stackb, t_pscount *ct)
{
	if (ct->posmaxb != 0)
	{
		if (ct->posmaxb > ct->lenb / 2)
			while (ct->posmaxb++ < ct->lenb)
				ct->numop += rrb_op(stackb);
		else
			while (ct->posmaxb-- > 0)
				ct->numop += rb_op(stackb);
	}
}

void	bothrotator(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	while (ct->indexb > 0 && ct->indexa > 0
		&& ct->indexb < ct->lenb / 2 && ct->indexa < ct->lena / 2)
	{
		ct->numop += rr_op(stacka, stackb);
		ct->indexa--;
		ct->indexb--;
	}
	while (ct->indexb > (ct->lenb / 2) + 1 && ct->indexa > (ct->lena / 2) + 1
		&& ct->indexb < ct->lenb && ct->indexa < ct->lena)
	{
		ct->numop += rrr_op(stacka, stackb);
		ct->indexa++;
		ct->indexb++;
	}
}

void	moves(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	bothrotator(stacka, stackb, ct);
	if (ct->indexb > 0 && ct->indexb < ct->lenb)
	{
		if (ct->indexb > (ct->lenb / 2) + 1)
			while (ct->indexb++ < ct->lenb)
				ct->numop += rrb_op(stackb);
		else
			while (ct->indexb-- > 0)
				ct->numop += rb_op(stackb);
	}
	if (ct->indexa > 0 && ct->indexa < ct->lena)
	{
		if (ct->indexa > (ct->lena / 2) + 1)
			while (ct->indexa++ < ct->lena)
				ct->numop += rra_op(stacka);
		else
			while (ct->indexa-- > 0)
				ct->numop += ra_op(stacka);
	}
	ct->numop += pb_op(stacka, stackb);
}

int	whenpivots(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	int	a;
	int	b;
	int	c;

	a = (*stacka)->data;
	b = (*stacka)->next->data;
	c = (*stacka)->next->next->data;
	if (c < (*stackb)->data)
	{
		while ((*stackb)->data > c)
			ct->numop += pa_op(stacka, stackb);
	}
	ct->numop += rra_op(stacka);
	while (*stackb && (*stackb)->data > b)
		ct->numop += pa_op(stacka, stackb);
	ct->numop += rra_op(stacka);
	while (*stackb && (*stackb)->data > a)
		ct->numop += pa_op(stacka, stackb);
	ct->numop += rra_op(stacka);
	while (*stackb)
		ct->numop += pa_op(stacka, stackb);
	return (0);
}

int	when3stacka(t_psstack **stacka, t_pscount *ct)
{
	ct->a = (*stacka)->data;
	ct->b = (*stacka)->next->data;
	ct->c = (*stacka)->next->next->data;
	if (checkascending(*stacka) == 0)
		return (0);
	else if (ct->a > ct->b && ct->c > ct->a)
		return (ct->numop += sa_op(stacka), 1);
	else if (ct->a < ct->c && ct->c < ct->b)
		return (ct->numop += sa_op(stacka), ct->numop += ra_op(stacka), 2);
	else if (ct->c < ct->b && ct->b > ct->a)
		return (ct->numop += rra_op(stacka), 3);
	else if (ct->a > ct->b && ct->b < ct->c)
		return (ct->numop += ra_op(stacka), 4);
	else if (ct->a > ct->b && ct->b > ct->c)
		return (ct->numop += ra_op(stacka), ct->numop += sa_op(stacka), 5);
	return (6);
}
