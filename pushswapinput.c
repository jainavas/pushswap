/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswapinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:40:08 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 21:12:41 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Frees all allocated memory for stacks and counter structure
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 */
void	freepsw(t_psstack **stacka, t_psstack **stackb, t_pscount *ct)
{
    stackclear(stacka);
    stackclear(stackb);
    free(ct);
}

/**
 * @brief Parse arguments from a single string into stack A (split by spaces)
 * 
 * @param stacka Pointer to stack A
 * @param argv Array of argument strings
 * @param argc Argument count
 * @return int Returns -1 on error, 0 on success
 */
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
            stackadd_back(stacka, stacknew(ft_atoi(argv[i])));
        i++;
    }
    freedoublepointer(argv);
    return (0);
}

/**
 * @brief Parse arguments from multiple command-line args into stack A
 * 
 * @param stacka Pointer to stack A
 * @param argv Array of argument strings
 * @param argc Argument count
 * @return int Returns -1 on error, 0 on success
 */
int	args2(t_psstack **stacka, char **argv, int argc)
{
    int	i;

    i = 1;
    while (i < argc)
    {
        if (checkoverflow(argv[i]) == -1)
            return (-1);
        else
            stackadd_back(stacka, stacknew(ft_atoi(argv[i])));
        i++;
    }
    return (0);
}

/**
 * @brief Count the number of strings in a string array
 * 
 * @param res Array of strings
 * @return int Number of strings in the array
 */
int	strofstrlen(char **res)
{
    int	i;

    i = 0;
    if (res)
        while (res[i])
            i++;
    return (i);
}

/**
 * @brief Make small optimizations to stack B before processing
 * 
 * @param stacka Pointer to stack A
 * @param stackb Pointer to stack B
 * @param ct Pointer to counter structure
 */
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
