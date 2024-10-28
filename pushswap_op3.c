/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_op3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:13:35 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/28 16:21:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	rrr_op(t_psstack **stacka, t_psstack **stackb)
{
	if (rra_op(stacka) == 1 && rrb_op(stackb) == 1)
		return (ft_putstr_fd("rrr\n", 1), 1);
	return (0);
}
