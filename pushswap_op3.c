/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_op3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:13:35 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/29 20:27:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	rrr_op(t_psstack **stacka, t_psstack **stackb)
{
	if (rra_op(stacka) == 1 && rrb_op(stackb) == 1)
		return (1);
	return (0);
}

void verifierlinks(t_psstack **stack)
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