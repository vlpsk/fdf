/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:41:38 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 18:41:44 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	index;

	ch = (char)c;
	index = ft_strlen(s);
	s = s + index;
	while (index > 0)
	{
		if (*s == ch)
			return ((char *)s);
		s--;
		index--;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}
