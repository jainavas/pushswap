/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:42:03 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/21 19:42:03 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_psstack	*stacknew(int data)
{
	t_psstack *new;

	new = ft_calloc(1, sizeof(t_psstack));
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_psstack	*stacklast(t_psstack *lst)
{
	t_psstack	*tmp;

	tmp = stackfirst(lst);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_psstack	*stacksemilast(t_psstack *lst)
{
	t_psstack	*tmp;

	while (tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}

t_psstack	*stackfirst(t_psstack *lst)
{
	t_psstack	*tmp;

	tmp = lst;
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

void	stackclear(t_psstack **lst)
{
	t_psstack	*new;

	while (*lst != NULL)
	{
		new = *lst;
		*lst = new->next;
		free(new);
	}
}

void	stackadd_front(t_psstack **lst, t_psstack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
	}
	else
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
	}
}

void	stackadd_back(t_psstack **lst, t_psstack *new)
{
	t_psstack	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = stacklast(*(lst));
			new->next = NULL;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

int	stacksize(t_psstack *lst)
{
	t_psstack	*new;
	int		i;

	i = 0;
	new = stackfirst(lst);
	while (new)
	{
		new = new->next;
		i++;
	}
	return (i);
}
