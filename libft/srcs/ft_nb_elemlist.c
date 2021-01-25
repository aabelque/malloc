/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_elemlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:21:43 by aabelque          #+#    #+#             */
/*   Updated: 2018/01/17 16:49:53 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nb_elemlist(t_list *list)
{
	int	size;

	size = 0;
	if (list->next == NULL)
		return (0);
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}
