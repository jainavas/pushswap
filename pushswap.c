/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+           */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:21 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 21:07:55 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Checks if there are any duplicate integers in the stack
 * 
 * @param stack Pointer to the start of the stack to check
 * @return int Returns -1 if duplicates found, 0 if no duplicates
 */
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

/**
 * @brief Gets the index position of a specific number in the stack
 * 
 * @param stack Pointer to the stack to search in
 * @param num The number to search for
 * @return int Index of the number if found, -1 if not found
 */
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

/**
 * @brief Special handling for small number of elements (1-5)
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure with algorithm data
 * @return int Returns -1 if handled, 0 if not handled
 */
int	debuglilnum(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
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

/**
 * @brief Main algorithm (Turkish method) for sorting larger stacks
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure with algorithm data
 * @return int Always returns 0 on completion
 */
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

/**
 * @brief Main function - parses inputs and calls appropriate sort algorithms
 * 
 * @param argc Argument count
 * @param argv Argument values
 * @return int Returns -1 on error, 0 on success
 */
int	main(int argc, char**argv)
{
    t_psstack	*stacka;
    t_psstack	*stackb;
    t_pscount	*ct;

    ct = ft_calloc(1, sizeof(t_pscount));
    stacka = NULL;
    stackb = NULL;
    if (argc == 1)
        return (free(ct), ft_printf("Error\n"), -1);
    if (argc == 2)
        if (args(&stacka, ft_split(argv[1], ' '), argc) == -1)
            return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
    if (argc > 2)
        if (args2(&stacka, argv, argc) == -1)
            return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
    ct->numop = 0;
    ct->lena = stacksize(stacka);
    if (checkrepeat(stacka) == -1)
        return (freepsw(&stacka, &stackb, ct), ft_printf("Error\n"), -1);
    if (debuglilnum(&stacka, &stackb, ct) != -1)
        turc(&stacka, &stackb, ct);
    freepsw(&stacka, &stackb, ct);
    return (0);
}
