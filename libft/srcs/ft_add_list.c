/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:24 by aabelque          #+#    #+#             */
/*   Updated: 2018/01/16 15:31:44 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_list(t_list **list, char *str)
{
	t_list	*tmp;

	tmp = (t_list*)malloc(sizeof(*tmp));
	if (tmp)
	{
		tmp->str = str;
		tmp->next = *list;
	}
	*list = tmp;
}
