/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:21 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/24 23:16:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sa_op(t_psstack **stacka)
{
	t_psstack *tmp;

	if ((*stacka)->next == NULL)
		return (0);
	tmp = *stacka; // temp is 1
	*stacka = (*stacka)->next; // go to 2
	tmp->next = (*stacka)->next; // 1next is 2next
	(*stacka)->next = tmp; // 2next is 1
	(*stacka)->prev = NULL;
	(*stacka)->next->prev = *stacka;
	return (1);
}

int	sb_op(t_psstack **stackb)
{
	t_psstack *tmp;

	if ((*stackb)->next == NULL)
		return (0);
	tmp = (*stackb); // temp is 1
	*stackb = (*stackb)->next; // go to 2
	tmp->next = (*stackb)->next; // 1next is 2next
	(*stackb)->next = tmp; // 2next is 1
	(*stackb)->prev = NULL;
	(*stackb)->next->prev = *stackb;
	return (1);
}

int ss_op(t_psstack **stacka, t_psstack **stackb)
{
	if (sa_op(stacka) == 1 && sb_op(stackb) == 1)
		return (1);
	return (0);
}

int	pa_op(t_psstack **stacka, t_psstack **stackb)
{
	t_psstack	*tmp;

	if (*stackb == NULL)
		return (0);
	tmp = (*stackb)->next;
	if (tmp != NULL)
		tmp->prev = NULL;
	(*stackb)->next = *stacka;
	if (*stacka != NULL)
		(*stacka)->prev = *stackb;
	*stacka = *stackb;
	*stackb = tmp;
	return (1);	
}

int	pb_op(t_psstack **stacka, t_psstack **stackb)
{
	t_psstack	*tmp;

	if (*stacka == NULL)
		return (0);
	tmp = (*stacka)->next;
	tmp->prev = NULL;
	stackadd_front(stackb, *stacka);
	*stacka = tmp;
	return (1);
}

int	ra_op(t_psstack **stacka)
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
	return (1);
}

int	rb_op(t_psstack **stackb)
{
	t_psstack	*tmp;
	t_psstack	*last;

	if (stacksize(*stackb) == 2)
		return (sa_op(stackb));
	if (stacksize(*stackb) <= 1)
		return (0);
	tmp = *stackb;
	*stackb = (*stackb)->next;
	(*stackb)->prev = NULL;
	last = stacklast(*stackb);
	tmp->prev = last;
	tmp->next = NULL;
	last->next = tmp;
	return (1);
}

int rr_op(t_psstack **stacka, t_psstack **stackb)
{
	int	i;

	i = 0;
	if (ra_op(stacka) == 1 && rb_op(stackb) == 1)
		i++;
	return (i);
}

int	rra_op(t_psstack **stacka)
{
	t_psstack	*last;
	t_psstack	*prev_last;

	if (!(*stacka) || !(*stacka)->next)
		return (0);
	prev_last = stacksemilast(*stacka);
	last = stacklast(*stacka);
	if (*stacka)
	{
		last->prev = NULL;
		last->next = *stacka;
		last->next->prev = last;
		prev_last->next = NULL;
		*stacka = last;
	}
	return (1);
}

int	rrb_op(t_psstack **stackb)
{
	t_psstack	*acttail;
	t_psstack	*newtail;
	t_psstack	*tmp;

	acttail = stacklast(*stackb);
	newtail = stacksemilast(*stackb);
	tmp = *stackb;
	*stackb = acttail;
	(*stackb)->next = tmp;
	(*stackb)->prev = NULL;
	newtail->next = NULL;
	return (1);
}

int rrr_op(t_psstack **stacka, t_psstack **stackb)
{
	if (rra_op(stacka) == 1 && rrb_op(stackb) == 1)
		return (1);
	return (0);
}

int	getmaxmin(t_psstack *stackb, t_pscount *ct)
{
	int	i;
	int	num;

	i = 0;
	if (ct->maxb != INT_MIN)
	{
		ct->posmaxb = getindex(stackb, ct->maxb);
		ct->posminb = getindex(stackb, ct->minb);
	}
	while (stackb)
	{
		num = stackb->data;
		if (num > ct->maxb)
		{
			ct->maxb = num;
			ct->posmaxb = i;
		}
		if (num < ct->minb)
		{
			ct->minb = num;
			ct->posminb = i;
		}
		i++;
		stackb = stackb->next;
	}
}

int	checkrepeat(t_psstack *stack)
{
	t_psstack	*parse = NULL;
	int		num;

	num = stack->data;
	parse = stack->next;
	while (parse)
	{
		if (num == parse->data)
			return (-1);
		parse = parse->next;
	}
	if (stack->next == NULL)
		return (0);
	return (checkrepeat(stack->next));
}

int checkdescending(t_psstack *stacka)
{
	while (stacka->next)
	{
		if (stacka->data < stacka->next->data)
			return (-1);
		stacka = stacka->next;
	}
	return (0);
}

int checkascending(t_psstack *stacka)
{
	while (stacka->next)
	{
		if (stacka->data > stacka->next->data)
			return (-1);
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
	printf("\nnum ops: %d\n", ct->numop);
}

int	getindex(t_psstack *stack, int num)
{
	int	i;

	i = 0;
	stack = stackfirst(stack);
	while (stack)
	{
		if (stack->data == num)
			return (i);
		i++;
		stack = stack->next;
	}
	return (-1);
}

int	getcorrectpos(int num, t_psstack *stackb, t_pscount *ct)
{
	int i;
	t_psstack	*parse;
	t_psstack	*tmp;

	i = 0;
	parse = stackb;
	while (parse)
	{
		if (!parse->prev)
			tmp = stacklast(parse);
		else
			tmp = parse->prev;
		if (num > parse->data && num < tmp->data && ct->maxb != parse->data)
			return (i);
		i++;
		parse = parse->next;
	}
	return (1000);
}

int	pricemax(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
	int		i;

	while (stacka->data < ct->maxb)
		stacka = stacka->next;
	if (getindex(stacka, stacka->data) >= (stacksize(stacka)/2) + 1)
		i = stacksize(stacka) - getindex(stacka, stacka->data);
}

int	getpricemov(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
	// index a, index b y relaciones entre num siempre tiene que ser introducido cuando el mayor que el es el ultimo y el menor que el es el primero
	// retorna index a del que deberia ser mas barato de cambiar
	t_psstack	*parse;
	int		tmp;
	int		price;
	int		tmpprice;
	int		localindexa;
	int		localindexb;

	price = 64643;
	localindexa = 0;
	parse = stackb;
	while (stacka)
	{
		parse = stackb;
		localindexb = 0;
		while (localindexb < stacksize(stackb) && parse)
		{
			tmpprice = 483332;
			tmp = localindexb;
			getmaxmin(stackfirst(stackb), ct);
			if (stacka->data > ct->minb && stacka->data < ct->maxb)
			{
				tmpprice = 0;
				localindexb = getcorrectpos(stacka->data, stackb, ct);
				tmpprice += localindexa;
				tmpprice += localindexb;
				tmpprice++;
			}
			else if (stacka->data > ct->maxb || stacka->data < ct->minb)
			{
				tmpprice = 0;
				localindexb = ct->posmaxb;
				tmpprice += localindexa;
				tmpprice += localindexb;
				tmpprice++;
			}
			if (tmpprice < price)
			{
				price = tmpprice;
				ct->indexa = localindexa;
				ct->indexb = localindexb;
			}
			localindexb = tmp;
			localindexb++;
			parse = parse->next;
		}
		localindexa++;
		stacka = stacka->next;
	}
	return (price);
}

int	whenpivots(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	int	a;
	int	b;
	int	c;
	int	i;

	a = (*stacka)->data;
	b = (*stacka)->next->data;
	c = (*stacka)->next->next->data;
	if (c < (*stackb)->data)
	{
		while ((*stackb)->data > c)
			ct->numop += pa_op(stacka, stackb);
	}
		ct->numop += rra_op(stacka);
		while ((*stackb)->data > b)
			ct->numop += pa_op(stacka, stackb);
		ct->numop += rra_op(stacka);
		while ((*stackb)->data > a)
			ct->numop += pa_op(stacka, stackb);
		ct->numop += rra_op(stacka);
		while (*stackb)
			ct->numop += pa_op(stacka, stackb);
	return (0);
}

int	when3stacka(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	if (checkascending(*stacka) == 0)
		return (0);
	else if ((*stacka)->data > (*stacka)->next->data && (*stacka)->next->next->data > (*stacka)->data) // BAC
		ct->numop += sa_op(stacka);
	else if ((*stacka)->data < (*stacka)->next->data && (*stacka)->next->next->data < (*stacka)->next->data)	// ACB
	{
		ct->numop += sa_op(stacka);
		ct->numop += ra_op(stacka);
	}
	else if ((*stacka)->next->next->data < (*stacka)->next->data && (*stacka)->next->data > (*stacka)->data) // BCA
		ct->numop += rra_op(stacka);
	else if ((*stacka)->data > (*stacka)->next->data && (*stacka)->next->data < (*stacka)->next->next->data) // CAB
		ct->numop += ra_op(stacka);
	else if ((*stacka)->data > (*stacka)->next->data && (*stacka)->next->data > (*stacka)->next->next->data) // CBA
	{
		ct->numop += sa_op(stacka);
		ct->numop += rra_op(stacka);
	}
	return (0);
}

int	turc(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	int		price;
	t_psstack	*parse;
	int		i;

	ct->numop += pb_op(stacka, stackb);
	ct->numop += pb_op(stacka, stackb);
	ct->maxb = INT_MIN;
	ct->minb = INT_MAX;
	getmaxmin(*stackb, ct);
	while (stacksize(*stacka) > 3)
	{
		getpricemov(*stacka, *stackb, ct);
		if (ct->indexa > 0)
			while (ct->indexa-- > 0)
			{
				if (ct->indexb-- > 0)
					ct->numop += rr_op(stacka, stackb);
				else
					ct->numop += ra_op(stacka);
			}
		if (ct->indexb > 0)
			while (ct->indexb-- > 0)
				ct->numop += rb_op(stackb);
		ct->numop += pb_op(stacka, stackb);
		getmaxmin(*stackb, ct);
	}
	when3stacka(stacka, stackb, ct);
	if (ct->posmaxb > stacksize(*stackb)/2)
		while (ct->posmaxb++ < stacksize(*stackb))
			ct->numop += rrb_op(stackb);
	else
		while (ct->posmaxb--)
			ct->numop += rb_op(stackb);
	whenpivots(stacka, stackb, ct);
	return (0);
}

int	main(int argc, char**argv)
{
	int	i;
	int	num;
	t_psstack *stacka = NULL;
	t_psstack *stackb = NULL;
	t_pscount *ct;

	ct = ft_calloc(1, sizeof(t_pscount));
	i = 1;
	ct->numop = 0;
	while (i < argc)
		stackadd_front(&stacka, stacknew(ft_atoi(argv[i++])));
	if (checkrepeat(stacka) == -1)
		return (ft_printf("repes"), -1);
	turc(&stacka, &stackb, ct);
	if (checkascending(stacka) == -1)
	{
		printf("\nMAL ||%d||\n", ct->numop);
		printstacks(stacka, stackb, ct);
	}
	else
		printf("\nBIEN ||%d||\n", ct->numop);
	stackclear(&stacka);
	return (0);
}
