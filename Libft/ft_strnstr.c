/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:53:34 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 19:53:36 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	l;
	char	*ptr;
	char	*pattern;

	l = ft_strlen(needle);
	if (l == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*haystack && len >= l && len)
	{
		pattern = (char *)needle;
		ptr = (char *)haystack;
		while (*pattern == *haystack && *haystack && *pattern)
		{
			pattern++;
			haystack++;
		}
		if (!*pattern)
			return (ptr);
		haystack = ptr + 1;
		len--;
	}
	return (NULL);
}
