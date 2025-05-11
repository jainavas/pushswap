/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswapprices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:59:48 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 21:15:59 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Find the correct position for a number in stack B
 * 
 * @param num Number to be positioned
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 * @return int The index position where the number should be placed
 */
int	getcorrectpos(int num, t_psstack *stackb, t_pscount *ct)
{
    int			i;
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
    return (10000);
}

/**
 * @brief Calculate the cost (price) for handling max or min values
 * 
 * @param ct Pointer to counter structure with algorithm data
 */
void	price2(t_pscount *ct)
{
    ct->tmpprice = 0;
    ct->localindexb = ct->posmaxb;
    if (ct->localindexa > (ct->lena / 2) + 1)
        ct->tmpprice += ct->lena - ct->localindexa;
    else
        ct->tmpprice += ct->localindexa;
    if (ct->localindexb > (ct->lenb / 2) + 1)
        ct->tmpprice += ct->lenb - ct->localindexb;
    else
        ct->tmpprice += ct->localindexb;
    ct->tmpprice++;
}

/**
 * @brief Calculate the cost (price) for standard values within min-max range
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure with algorithm data
 */
void	price1(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
    ct->tmpprice = 0;
    ct->localindexb = getcorrectpos(stacka->data, stackb, ct);
    if (ct->localindexa > (ct->lena / 2) + 1)
        ct->tmpprice += ct->lena - ct->localindexa;
    else
        ct->tmpprice += ct->localindexa;
    if (ct->localindexb > (ct->lenb / 2) + 1)
        ct->tmpprice += ct->lenb - ct->localindexb;
    else
        ct->tmpprice += ct->localindexb;
    ct->tmpprice++;
}

/**
 * @brief Calculate and compare the cost of moving current element from A to B
 * 
 * @param stacka Pointer to current element in stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure with algorithm data
 */
void	priceget(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
    ct->tmpprice = INT_MAX;
    ct->tmp = ct->localindexb;
    if (stacka->data > ct->minb && stacka->data < ct->maxb)
        price1(stacka, stackb, ct);
    else if (stacka->data > ct->maxb || stacka->data < ct->minb)
        price2(ct);
    if (ct->tmpprice < ct->price)
    {
        ct->price = ct->tmpprice;
        ct->indexa = ct->localindexa;
        ct->indexb = ct->localindexb;
    }
    ct->localindexb = ct->tmp;
    ct->localindexb++;
}

/**
 * @brief Find the cheapest element to move from stack A to stack B
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure with algorithm data
 * @return int The lowest cost (price) found
 */
int	getpricemov(t_psstack *stacka, t_psstack *stackb, t_pscount *ct)
{
    ct->price = INT_MAX;
    ct->localindexa = 0;
    while (stacka)
    {
        priceget(stacka, stackb, ct);
        ct->localindexa++;
        stacka = stacka->next;
    }
    return (ct->price);
}
