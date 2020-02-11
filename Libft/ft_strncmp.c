/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:31:10 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/09 14:31:12 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t index;

	if (n == 0)
		return (0);
	index = 0;
	while (s1[index] == s2[index] && n--)
	{
		if ((s1[index] == '\0' && s2[index] == '\0') || n == 0)
			return (0);
		else
			index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
