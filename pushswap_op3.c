/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_op3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:13:35 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/30 16:45:20 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	rrr_op(t_psstack **stacka, t_psstack **stackb)
{
	if (rra_op(stacka, 1) == 1 && rrb_op(stackb, 1) == 1)
		return (op_print(6), 1);
	return (0);
}

void	verifierlinks(t_psstack **stack)
{
	t_psstack	*tmp;
	t_psstack	*parse;

	parse = *stack;
	tmp = (*stack)->next;
	while (tmp)
	{
		tmp->prev = parse;
		parse = parse->next;
		tmp = tmp->next;
	}
}

void	op_print(int num)
{
	if (num == 1)
		ft_printf("ra\n");
	if (num == 2)
		ft_printf("rb\n");
	if (num == 3)
		ft_printf("rr\n");
	if (num == 4)
		ft_printf("rra\n");
	if (num == 5)
		ft_printf("rrb\n");
	if (num == 6)
		ft_printf("rrr\n");
}
