/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:57:52 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/10 14:58:02 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*get_newstr(size_t len, size_t i, char const *s)
{
	char	*newstr;
	size_t	j;

	newstr = (char *)malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	j = 0;
	while (len)
	{
		newstr[j++] = s[i++];
		len--;
	}
	newstr[j] = '\0';
	return (newstr);
}

char			*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && len > 0)
	{
		len--;
		i++;
	}
	return (get_newstr(len, i, s));
}
