/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:04:13 by sgisele           #+#    #+#             */
/*   Updated: 2019/04/11 20:04:15 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*beginlst;

	if (lst == NULL || f == NULL)
		return (NULL);
	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == NULL)
		return (NULL);
	newlst = NULL;
	beginlst = newlst;
	while (lst != NULL)
	{
		if (newlst != NULL)
		{
			ft_lstadd(&(newlst->next), f(lst));
			newlst = newlst->next;
		}
		else
		{
			ft_lstadd(&newlst, f(lst));
			beginlst = newlst;
		}
		lst = lst->next;
	}
	return (beginlst);
}
