/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:07:00 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/11 15:07:02 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_n_size(unsigned int n)
{
	int	size;

	size = 0;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

char			*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	index;
	int				size;

	if (n < 0)
		nb = (unsigned int)(n * -1);
	else
		nb = (unsigned int)n;
	size = get_n_size(nb);
	if (n < 0)
		size++;
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
