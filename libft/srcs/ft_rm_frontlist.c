/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_frontlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:08:20 by aabelque          #+#    #+#             */
/*   Updated: 2018/01/16 15:36:37 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rm_frontlist(t_list **list)
{
	t_list *tmp;

	if (*list)
	{
		tmp = (*list)->next;
		(*list)->next = NULL;
		free(*list);
		*list = tmp;
	}
}
