/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:47 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/24 21:17:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft_ext/libft.h"
# include "libft_ext/ft_printf.h"

typedef struct pushswap
{
	int		numop;
	int		len;
	int		maxb;
	int		minb;
	int		posmaxb;
	int		posminb;
	int		indexb;
	int		indexa;
	int		maxall;
	int		minall;
}	t_pscount;

typedef struct stack
{
	int				data;
	struct stack	*next;
	struct stack	*prev;
}	t_psstack;


int				checkascending(t_psstack *stacka);
t_psstack		*stacknew(int data);
t_psstack		*stacklast(t_psstack *lst);
t_psstack		*stacksemilast(t_psstack *lst);
t_psstack		*stackfirst(t_psstack *lst);
int				stacksize(t_psstack *lst);
void			stackclear(t_psstack **lst);
int				getindex(t_psstack *stack, int num);
void			stackadd_front(t_psstack **lst, t_psstack *new);
void			stackadd_back(t_psstack **lst, t_psstack *new);
void			printstacks(t_psstack *stacka, t_psstack *stackb, t_pscount *ct);

#endif