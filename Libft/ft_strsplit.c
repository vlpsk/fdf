/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:55:12 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/10 15:55:14 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		get_token_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static	char	*get_token(char const *s, char c, size_t i)
{
	size_t	j;
	size_t	len_token;
	char	*token;

	len_token = 0;
	while (s[i + len_token] != c && s[i + len_token] != '\0')
		len_token++;
	token = (char *)malloc(sizeof(char) * (len_token + 1));
	if (token == NULL)
		return (NULL);
	j = 0;
	while (len_token)
	{
		token[j++] = s[i++];
		len_token--;
	}
	token[j] = '\0';
	return (token);
}

static void		*free_memmory(char **arr, int count)
{
	while (count)
	{
		free(arr[count]);
		count--;
	}
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	count;

	if (s == NULL)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (get_token_count(s, c) + 1))))
		return (NULL);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			if ((arr[count] = get_token(s, c, i)) == NULL)
				return (free_memmory(arr, count));
			i = i + ft_strlen(arr[count]);
			count++;
		}
	}
	arr[count] = 0;
	return (arr);
}
