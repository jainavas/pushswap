/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswapmoves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:04:10 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 21:14:16 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Rotates stack B to put the maximum value at the top
 * 
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 */
void	putbigfirst(t_psstack **stackb, t_pscount *ct)
{
    if (ct->posmaxb != 0)
    {
        if (ct->posmaxb > ct->lenb / 2)
            while (ct->posmaxb++ < ct->lenb)
                ct->numop += rrb_op(stackb, 0);
        else
            while (ct->posmaxb-- > 0)
                ct->numop += rb_op(stackb, 0);
    }
}

/**
 * @brief Performs simultaneous rotations on both stacks when possible
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 */
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

/**
 * @brief Executes all necessary moves to position elements correctly before push
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 */
void	moves(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
    bothrotator(stacka, stackb, ct);
    if (ct->indexb > 0 && ct->indexb < ct->lenb)
    {
        if (ct->indexb > (ct->lenb / 2) + 1)
            while (ct->indexb++ < ct->lenb)
                ct->numop += rrb_op(stackb, 0);
        else
            while (ct->indexb-- > 0)
                ct->numop += rb_op(stackb, 0);
    }
    if (ct->indexa > 0 && ct->indexa < ct->lena)
    {
        if (ct->indexa > (ct->lena / 2) + 1)
            while (ct->indexa++ < ct->lena)
                ct->numop += rra_op(stacka, 0);
        else
            while (ct->indexa-- > 0)
                ct->numop += ra_op(stacka, 0);
    }
    ct->numop += pb_op(stacka, stackb);
}

/**
 * @brief Final step: pushes elements from B to A in correct order
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 * @return int Always returns 0 on completion
 */
int	whenpivots(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
    int	a;
    int	b;
    int	c;

    a = (*stacka)->next->prev->data;
    b = (*stacka)->next->next->prev->data;
    c = (*stacka)->next->next->data;
    while ((*stackb)->data > c)
        ct->numop += pa_op(stacka, stackb);
    ct->numop += rra_op(stacka, 0);
    while (*stackb && (*stackb)->data > b)
        ct->numop += pa_op(stacka, stackb);
    ct->numop += rra_op(stacka, 0);
    while (*stackb && (*stackb)->data > a)
        ct->numop += pa_op(stacka, stackb);
    getmaxmin(*stacka, ct);
    if (*stackb || ct->posminb != 0)
        ct->numop += rra_op(stacka, 0);
    while (*stackb)
        ct->numop += pa_op(stacka, stackb);
    return (0);
}

/**
 * @brief Special sorting algorithm for exactly 3 elements in stack A
 * 
 * @param stacka Pointer to stack A
 * @param ct Pointer to counter structure
 * @return int Returns number of case handled (1-6) or 0 if already sorted
 */
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
        return (ct->numop += sa_op(stacka), ct->numop += ra_op(stacka, 0), 2);
    else if (ct->c < ct->b && ct->b > ct->a)
        return (ct->numop += rra_op(stacka, 0), 3);
    else if (ct->a > ct->b && ct->b < ct->c)
        return (ct->numop += ra_op(stacka, 0), 4);
    else if (ct->a > ct->b && ct->b > ct->c)
        return (ct->numop += ra_op(stacka, 0), ct->numop += sa_op(stacka), 5);
    return (6);
}
