/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:47 by jainavas          #+#    #+#             */
/*   Updated: 2025/01/24 17:40:09 by jainavas         ###   ########.fr       */
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
	int		lenb;
	int		lena;
	int		maxb;
	int		minb;
	int		posmaxb;
	int		posminb;
	int		indexb;
	int		indexa;
	int		tmp;
	int		price;
	int		tmpprice;
	int		localindexa;
	int		localindexb;
	int		a;
	int		b;
	int		c;
}	t_pscount;

typedef struct stack
{
	int				data;
	struct stack	*next;
	struct stack	*prev;
}	t_psstack;
// prices
int			getcorrectpos(int num, t_psstack *stackb, t_pscount *ct);
void		price2(t_pscount *ct);
void		price1(t_psstack *stacka, t_psstack *stackb, t_pscount *ct);
void		priceget(t_psstack *stacka, t_psstack *stackb, t_pscount *ct);
int			getpricemov(t_psstack *stacka, t_psstack *stackb, t_pscount *ct);
void		getmaxmin(t_psstack *stackb, t_pscount *ct);
// stack manage
t_psstack	*stacknew(int data);
t_psstack	*stacklast(t_psstack *lst);
t_psstack	*stackfirst(t_psstack *lst);
int			stacksize(t_psstack *lst);
void		stackclear(t_psstack **lst);
void		freepsw(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);
int			getindex(t_psstack *stack, int num);
void		stackadd_front(t_psstack **lst, t_psstack *new);
void		stackadd_back(t_psstack **lst, t_psstack *new);
void		printstacks(t_psstack *stacka, t_psstack *stackb, t_pscount *ct);
// moves
int			when3stacka(t_psstack **stacka, t_pscount *ct);
int			whenpivots(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);
void		moves(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);
void		bothrotator(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);
void		putbigfirst(t_psstack **stackb, t_pscount *ct);
// operations
int			sa_op(t_psstack **stacka);
int			sb_op(t_psstack **stackb);
int			ss_op(t_psstack **stacka, t_psstack **stackb);
int			pa_op(t_psstack **stacka, t_psstack **stackb);
int			pb_op(t_psstack **stacka, t_psstack **stackb);
int			rb_op(t_psstack **stackb, int both);
int			ra_op(t_psstack **stacka, int both);
int			rr_op(t_psstack **stacka, t_psstack **stackb);
int			rrr_op(t_psstack **stacka, t_psstack **stackb);
int			rra_op(t_psstack **stacka, int both);
int			rrb_op(t_psstack **stackb, int both);
void		op_print(int num);
// checks
int			checkrepeat(t_psstack *stack);
int			debuglilnum(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);
int			checkascending(t_psstack *stacka);
int			checkoverflow(const char *str);
int			args(t_psstack **stacka, char **argv, int argc);
int			args2(t_psstack **stacka, char **argv, int argc);
int			strofstrlen(char **res);
void		verifierlinks(t_psstack **stack);
void		lilchanges(t_psstack **stacka, t_psstack **stackb, t_pscount *ct);

#endif