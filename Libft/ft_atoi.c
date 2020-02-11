/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:36:32 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/09 14:36:34 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	i;
	int			sign;

	i = 0;
	sign = 1;
	while (*str == '\n' || *str == '\t' || *str == '\v' || *str == ' ' ||
			*str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (i > 922337203685477580 && *str > '7' && sign == 1)
			return (-1);
		if (i > 922337203685477580 && *str > '8' && sign == -1)
			return (0);
		i = i * 10 + ((int)(*str - 48));
		str++;
	}
	return ((int)(i * sign));
}
