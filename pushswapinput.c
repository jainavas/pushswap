/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswapinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:40:08 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/29 22:59:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void freepsw(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	stackclear(stacka);
	stackclear(stackb);
	free(ct);
}

int	args(t_psstack **stacka, char **argv, int argc)
{
	int	i;

	i = 0;
	argc = argc + i;
	while (argv[i])
	{
		if (checkoverflow(argv[i]) == -1)
			return (freedoublepointer(argv), -1);
		else
			stackadd_front(stacka, stacknew(ft_atoi(argv[i])));
		i++;
	}
	freedoublepointer(argv);
	return (0);
}

int	args2(t_psstack **stacka, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (checkoverflow(argv[i]) == -1)
			return (-1);
		else
			stackadd_front(stacka, stacknew(ft_atoi(argv[i])));
		i++;
	}
	return (0);
}

int	strofstrlen(char **res)
{
	int	i;

	i = 0;
	if (res)
		while (res[i])
			i++;
	return (i);
}

void	lilchanges(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
	if ((*stackb)->data > (*stackb)->next->data
		&& (*stacka)->data > (*stackb)->next->data
		&& (*stacka)->data < (*stackb)->data)
		ct->numop += sb_op(stackb);
	else if ((*stackb)->data < (*stackb)->next->data
		&& ((*stacka)->data > (*stackb)->next->data
		|| (*stacka)->data < (*stackb)->data))
		ct->numop += sb_op(stackb);
}