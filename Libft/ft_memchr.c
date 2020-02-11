/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:35:12 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/05 18:35:14 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*cs;

	ch = (unsigned char)c;
	cs = (unsigned char *)s;
	while (n--)
	{
		if (*cs == ch)
			return (cs);
		cs++;
	}
	return (NULL);
}
