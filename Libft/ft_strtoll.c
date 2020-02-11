/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:29:42 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/16 17:29:44 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			determine_base(const char *str, int base)
{
	int	mybase;

	if (base == 0)
	{
		if (str[0] == '0' && str[1] == 'x')
		{
			mybase = 16;
			str += 2;
		}
		else if (str[0] == '0')
		{
			mybase = 8;
			str++;
		}
		else
			mybase = 10;
	}
	else
		mybase = base;
	return (mybase);
}

static	long long	calculate(long long num, int mybase, const char *str)
{
	char		*alpha_lower;
	char		*alpha_upper;

	alpha_lower = "0123456789abcdefghijklmnopqrstuvwxyz";
	alpha_upper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (*str >= 'a' && *str <= alpha_lower[mybase - 1])
		num = num * mybase + ((int)(*str - 'a' + 10));
	else if (*str >= 'A' && *str <= alpha_upper[mybase - 1])
		num = num * mybase + ((int)(*str - 'A' + 10));
	return (num);
}

static	long long	convert_strtoll(const char *str, char **endptr, int mybase,
	int sign)
{
	long long	num;
	char		*alpha_lower;
	char		*alpha_upper;

	alpha_lower = "0123456789abcdefghijklmnopqrstuvwxyz";
	alpha_upper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	num = 0;
	while ((*str >= '0' && *str <= '9')
		|| (*str >= 'a' && *str <= alpha_lower[mybase - 1])
		|| (*str >= 'A' && *str <= alpha_upper[mybase - 1]))
	{
		if (num > 922337203685477580 && *str > '7' && sign == 1)
			return (-1);
		if (num > 922337203685477580 && *str > '8' && sign == -1)
			return (0);
		if (*str >= '0' && *str <= '9')
			num = num * mybase + ((int)(*str - '0'));
		else if (mybase > 10)
			num = calculate(num, mybase, str);
		str++;
		endptr++;
	}
	return (num);
}

long long			ft_strtoll(const char *str, char **endptr, int base)
{
	int			sign;
	long long	num;
	int			mybase;

	if (str == NULL)
		return (0);
	sign = 1;
	num = 0;
	mybase = determine_base(str, base);
	*endptr = (char *)str;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = sign * (-1);
		str++;
	}
	num = convert_strtoll(str, endptr, mybase, sign);
	return (num * sign);
}
