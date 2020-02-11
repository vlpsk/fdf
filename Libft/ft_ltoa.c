/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:38:48 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/16 20:38:50 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		get_n_size(long long n)
{
	unsigned int		size;
	unsigned long long	nb;

	size = 0;
	nb = 0;
	if (n < 0)
	{
		nb = (unsigned long long)(n * (-1));
		size++;
	}
	else
		nb = (unsigned long long)n;
	while (nb >= 10)
	{
		nb /= 10;
		size++;
	}
	return (size + 1);
}

char					*ft_ltoa(long long n)
{
	char				*str;
	unsigned long long	nb;
	unsigned int		index;
	unsigned int		size;

	if (n < 0)
		nb = (unsigned long long)(n * -1);
	else
		nb = (unsigned long long)n;
	size = get_n_size(n);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	index = size - 1;
	while (nb >= 10)
	{
		str[index--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[index] = (char)(nb % 10 + 48);
	str[size] = '\0';
	return (str);
}
