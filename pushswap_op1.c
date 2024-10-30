/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_op1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:06:36 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/29 22:08:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sa_op(t_psstack **stacka)
{
	t_psstack	*tmp;

	if (!*stacka || (*stacka)->next == NULL)
		return (0);
	tmp = *stacka;
	*stacka = (*stacka)->next;
	tmp->next = (*stacka)->next;
	(*stacka)->next = tmp;
	(*stacka)->prev = NULL;
	(*stacka)->next->prev = *stacka;
	verifierlinks(stacka);
	return (1);
}

int	sb_op(t_psstack **stackb)
{
	t_psstack	*tmp;

	if (!*stackb || (*stackb)->next == NULL)
		return (0);
	tmp = (*stackb);
	*stackb = (*stackb)->next;
	tmp->next = (*stackb)->next;
	(*stackb)->next = tmp;
	(*stackb)->prev = NULL;
	(*stackb)->next->prev = *stackb;
	verifierlinks(stackb);
	return (1);
}

int	ss_op(t_psstack **stacka, t_psstack **stackb)
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
	stackadd_front(stacka, *stackb);	
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
