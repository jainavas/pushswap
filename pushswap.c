/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:21 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/29 23:00:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	checkrepeat(t_psstack *stack)
{
	t_psstack	*parse;
	int			num;

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

int	debuglilnum(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	ct->lena = stacksize(*stacka);
	if (ct->lena == 2)
	{
		if ((*stacka)->data > (*stacka)->next->data)
			return (ct->numop += sa_op(stacka), -1);
		return (-1);
	}
	if (ct->lena == 1)
		return (-1);
	if (ct->lena == 3)
		return (when3stacka(stacka, ct), -1);
	if (ct->lena == 4)
	{
		ct->numop += pb_op(stacka, stackb);
		when3stacka(stacka, ct);
		return (whenpivots(stacka, stackb, ct), -1);
	}
	if (ct->lena == 5)
	{
		ct->numop += pb_op(stacka, stackb);
		ct->numop += pb_op(stacka, stackb);
		lilchanges(stacka, stackb, ct);
		when3stacka(stacka, ct);
		return (whenpivots(stacka, stackb, ct), -1);
	}
	return (0);
}

int	turc(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	ct->numop += pb_op(stacka, stackb);
	ct->numop += pb_op(stacka, stackb);
	ct->maxb = INT_MIN;
	ct->minb = INT_MAX;
	getmaxmin(*stackb, ct);
	lilchanges(stacka, stackb, ct);
	while (ct->lena > 3)
	{
		getpricemov(*stacka, *stackb, ct);
		moves(stacka, stackb, ct);
		getmaxmin(*stackb, ct);
		ct->lena = stacksize(*stacka);
		ct->lenb = stacksize(*stackb);
	}
	when3stacka(stacka, ct);
	putbigfirst(stackb, ct);
	whenpivots(stacka, stackb, ct);
	return (0);
}

int	main(int argc, char**argv)
{
	t_psstack	*stacka;
	t_psstack	*stackb;
	t_pscount	*ct;
	char 		**res;

	ct = ft_calloc(1, sizeof(t_pscount));
	stacka = NULL;
	stackb = NULL;
	if (argc == 2)
	{
		res = ft_split(argv[1], ' ');
		if (args(&stacka, res, argc) == -1)
			return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
	}
	else if (argc > 2)
		if (args2(&stacka, argv, argc) == -1)
			return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
	ct->numop = 0;
	if (checkrepeat(stacka) == -1)
		return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
	if (debuglilnum(&stacka, &stackb, ct) != -1)
		turc(&stacka, &stackb, ct);
	if (checkascending(stacka) != 0)
		printf("MAL ||%d|| num mal:%d\n", ct->numop, checkascending(stacka));
	else
		printf("		WIN ||%d||\n", ct->numop);
	printstacks(stacka, stackb, ct);
	freepsw(&stacka, &stackb, ct);
	return (0);
}
