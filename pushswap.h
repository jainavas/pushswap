/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:06:47 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/19 19:01:12 by jainavas         ###   ########.fr       */
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
}	t_pscount;

int		checkascending(t_list *stacka);
void	printstacks(t_list *stacka, t_list *stackb, t_pscount *ct);


#endif