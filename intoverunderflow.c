/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intoverunderflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 02:10:56 by jainavas          #+#    #+#             */
/*   Updated: 2024/08/12 02:10:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ext/libft.h"

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	checkoverflow(const char *str)
{
	int		i;
	long	res;
	int		minus;

	i = spaces(str);
	minus = 1;
	res = 0;
	if (ft_isdigit((int)str[i]) == 0)
		return (-1);
	if (str[i] == '-')
	{
		minus = -minus;
		i++;
	}
	while (ft_isdigit((int)str[i]) == 1)
	{
		res *= 10;
		res += str[i] - '0';
		i++;
		if (res * minus > INT_MAX || res * minus < -2147483648)
			return (-1);
	}
	return (0);
}
