/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_endlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:06:47 by aabelque          #+#    #+#             */
/*   Updated: 2018/01/16 15:32:24 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_endlist(t_list **list, char *str)
{
	t_list *tmp;
	t_list *elem;

	elem = (t_list *)malloc(sizeof(*elem));
	elem->str = str;
	elem->next = NULL;
	if (*list == NULL)
		*list = elem;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = elem;
	}
}
