/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:21 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/19 19:38:30 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_list	*ft_lst1beforelast(t_list *lst)
{
	while (lst && lst->next->next)
		lst = lst->next;
	return (lst);
}

int	sa_op(t_list **stacka)
{
	t_list *tmp;

	if ((*stacka)->next == NULL)
		return (0);
	tmp = *stacka; // temp is 1
	*stacka = (*stacka)->next; // go to 2
	tmp->next = (*stacka)->next; // 1next is 2next
	(*stacka)->next = tmp; // 2next is 1
	return (1);
}

int	sb_op(t_list **stackb)
{
	t_list *tmp;

	if ((*stackb)->next == NULL)
		return (0);
	tmp = (*stackb); // temp is 1
	*stackb = (*stackb)->next; // go to 2
	tmp->next = (*stackb)->next; // 1next is 2next
	(*stackb)->next = tmp; // 2next is 1
	return (1);
}

int ss_op(t_list **stacka, t_list **stackb)
{
	if (sa_op(stacka) == 1 && sb_op(stackb) == 1)
		return (1);
	return (0);
}

int	pa_op(t_list **stacka, t_list **stackb)
{
	t_list	*tmp;

	if (*stackb == NULL)
		return (0);
	tmp = (*stackb)->next;
	ft_lstadd_front(stacka, *stackb);
	*stackb = tmp;
	return (1);
}

int	pb_op(t_list **stacka, t_list **stackb)
{
	t_list	*tmp;

	tmp = (*stacka)->next;
	if ((*stacka)->content == NULL)
		return (0);
	ft_lstadd_front(stackb, *stacka);
	*stacka = tmp;
	return (1);
}

int	ra_op(t_list **stacka)
{
	t_list	*tmp;
	t_list	*last;

	if (ft_lstsize(*stacka) == 2)
		return (sa_op(stacka));
	if (ft_lstsize(*stacka) <= 1)
		return (0);
	tmp = *stacka;
	*stacka = (*stacka)->next;
	last = ft_lstlast(*stacka);
	tmp->next = NULL;
	last->next = tmp;
	return (1);
}

int	rb_op(t_list **stackb)
{
	t_list	*tmp;

	if (ft_lstsize(*stackb) == 2)
		return (sb_op(stackb));
	if (ft_lstsize(*stackb) <= 1)
		return (0);
	tmp = *stackb;
	*stackb = (*stackb)->next;
	ft_lstadd_back(stackb, tmp);
	return (1);
}

int rr_op(t_list **stacka, t_list **stackb)
{
	if (ra_op(stacka) == 1 && rb_op(stackb) == 1)
		return (1);
	return (0);
}

int	rra_op(t_list **stacka)
{
	t_list	*acttail;
	t_list	*newtail;
	t_list	*tmp;

	acttail = ft_lstlast(*stacka);
	newtail = ft_lst1beforelast(*stacka);
	tmp = *stacka;
	*stacka = acttail;
	(*stacka)->next = tmp;
	newtail->next = NULL;
	return (1);
}

int	rrb_op(t_list **stackb)
{
	t_list	*acttail;
	t_list	*newtail;
	t_list	*tmp;

	if (ft_lstsize(*stackb) == 2)
		return (sb_op(stackb));
	acttail = ft_lstlast(*stackb);
	newtail = ft_lst1beforelast(*stackb);
	tmp = *stackb;
	*stackb = acttail;
	(*stackb)->next = tmp;
	newtail->next = NULL;
	return (1);
}

int rrr_op(t_list **stacka, t_list **stackb)
{
	if (rra_op(stacka) == 1 && rrb_op(stackb) == 1)
		return (1);
	return (0);
}

void	getmaxmin(t_list *stackb, t_pscount *ct)
{
	int	i;

	i = 0;
	ct->maxb = *(int *)stackb->content;
	ct->minb = *(int *)stackb->content;
	while (stackb)
	{
		if (*(int *)stackb->content > ct->maxb)
		{
			ct->maxb = *(int *)stackb->content;
			ct->posmaxb = i;
		}
		if (*(int *)stackb->content < ct->minb)
		{
			ct->minb = *(int *)stackb->content;
			ct->posminb = i;
		}
		i++;
		stackb = stackb->next;
	}
}

int	checkrepeat(t_list *stack)
{
	t_list	*parse = NULL;
	int		num;

	num = *(int *)stack->content;
	parse = stack->next;
	while (parse)
	{
		if (num == *(int *)parse->content)
			return (-1);
		parse = parse->next;
	}
	if (stack->next == NULL)
		return (0);
	return (checkrepeat(stack->next));
}

int checkascending(t_list *stacka)
{
	t_list *parse;

	parse = stacka->next;
	while (parse)
	{
		if (*(int *)stacka->content > *(int *)parse->content)
			return (-1);
		parse = parse->next;
		stacka = stacka->next;
	}
	return (0);
}

void	printstacks(t_list *stacka, t_list *stackb, t_pscount *ct)
{
	ft_printf("\nContenido a: \n");
	while (stacka)
	{
		ft_printf("%d ", *(int *)(stacka->content));
		stacka = stacka->next;
	}
	ft_printf("\nContenido b: \n");
	while (stackb)
	{
		ft_printf("%d ", *(int *)(stackb->content));
		stackb = stackb->next;
	}
	printf("\nnum ops: %d\n", ct->numop);
}

int	getindex(t_list *stack, int num)
{
	int	i;

	i = 0;
	while (stack)
	{
		if (*(int *)stack->content == num)
			return (i);
		i++;
		stack = stack->next;
	}
}

int	getpricemov(int index, int num, t_list *stackb, t_pscount *ct)
{
	int 	res;
	int 	diff;
	t_list	*parse;

	parse = stackb;
	if (index > ct->len/2)
		res = ct->len - index;
	else
		res = index;
	diff = *(int *)parse->content - num;
	while (parse)
	{
		if (*(int *)parse->content - num > 0 && *(int *)parse->content - num < diff)
			diff = *(int *)parse->content - num;
		parse = parse->next;
	}
	ct->indexb = getindex(stackb, num + diff);
	if (ct->indexb > ft_lstsize(stackb)/2)
		res += ft_lstsize(stackb) - ct->indexb;
	else
		res += ct->indexb;
	return (res);
}

int	turc(t_list **stacka, t_list **stackb, t_pscount *ct)
{
	int		price;
	t_list	*parse;
	int		i;

	i = 0;
	price = INT_MAX;
	ct->numop += pb_op(stacka, stackb);
	ct->numop += pb_op(stacka, stackb);
	ct->len = ft_lstsize(*stacka) - 2;
	getmaxmin(*stackb, ct);
	while (ft_lstsize(*stacka) > 3)
	{
		parse = *stacka;
		while (parse)
		{
			if (getpricemov(i, *(int *)parse->content, *stackb, ct) < price)
				price = getpricemov(i, *(int *)parse->content, *stackb, ct);
			i++;
			parse = parse->next;
		}
		while (i-- > 0 && ct->indexb-- > 0)
			ct->numop += rr_op(stacka, stackb);
		if (i-- > 0)
			ct->numop += ra_op(stacka);
		if (ct->indexb > 0)
			ct->numop += rb_op(stacka);
		ct->numop += pb_op(stacka, stackb);
		ct->len = ft_lstsize(*stacka);
	}
	while ((*stackb)->next)
	{
		ct->numop += rrb_op(stackb);
		ct->numop += pa_op(stacka, stackb);
	}
	ct->numop += pa_op(stacka, stackb);
	// if (*(int *)(*stacka)->content > *(int *)(*stacka)->next->content)
	printstacks(*stacka, *stackb, ct);
	return (0);
}

int	main(int argc, char**argv)
{
	int	i;
	int	*num;
	t_list *stacka = NULL;
	t_list *stackb = NULL;
	t_pscount *ct;

	ct = ft_calloc(1, sizeof(t_pscount));
	i = 1;
	ct->numop = 0;
	while (i < argc)
	{
		num = malloc(sizeof(int));
		*num = ft_atoi(argv[i++]);
		ft_lstadd_back(&stacka, ft_lstnew(num));
	}
	if (checkrepeat(stacka) == -1)
		return (ft_printf("repes"), -1);
	turc(&stacka, &stackb, ct);
	ft_lstclear(&stacka, free);
	return (0);
}
