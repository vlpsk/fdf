/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:33:52 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/03 17:33:56 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*buff;
	char	*str;

	len = 0;
	while (src[len] != '\0')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (str);
	buff = str;
	while (*src != '\0')
		*buff++ = *src++;
	*buff = '\0';
	return (str);
}
