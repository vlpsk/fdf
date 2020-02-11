/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:54:44 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/08 18:54:46 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;
	char	*ptr;
	char	*pattern;

	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (*haystack)
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
	}
	return (NULL);
}
