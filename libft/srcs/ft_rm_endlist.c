/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_endlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:17:53 by aabelque          #+#    #+#             */
/*   Updated: 2018/01/16 15:41:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rm_endlist(t_list **list)
{
	t_list *tmp;
	t_list *ptmp;

	if (*list)
	{
		tmp = (*list);
		ptmp = NULL;
		while (tmp->next != NULL)
		{
			ptmp = tmp;
			tmp = tmp->next;
		}
		ptmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}
