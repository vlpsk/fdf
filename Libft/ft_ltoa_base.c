/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:14:06 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/17 14:14:07 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		get_n_size(long long n, unsigned long long base)
{
	unsigned int		size;
	unsigned long long	nb;

	size = 0;
	if (n < 0)
	{
		nb = (unsigned long long)(n * (-1));
		size++;
	}
	else
		nb = (unsigned long long)n;
	while (nb >= base)
	{
		nb /= base;
		size++;
	}
	return (size + 1);
}

char					*ft_ltoa_base(long long n, unsigned long long base)
{
	char				*str;
	unsigned long long	nb;
	unsigned int		index;
	unsigned int		size;
	char				*ciphers;

	ciphers = "0123456789abcdef";
	if (n < 0)
		nb = (unsigned long long)(n * (-1));
	else
		nb = (unsigned long long)n;
	size = get_n_size(n, base);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	index = size - 1;
	while (nb >= base)
	{
		str[index--] = ciphers[nb % base];
		nb /= base;
	}
	str[index] = ciphers[nb % base];
	str[size] = '\0';
	return (str);
}
