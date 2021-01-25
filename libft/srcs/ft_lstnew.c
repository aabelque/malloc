/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:02:26 by aabelque          #+#    #+#             */
/*   Updated: 2018/03/05 13:51:29 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *maillon;

	if (!(maillon = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
	}
	else
	{
		if (!(maillon->content = malloc(sizeof(maillon->content)
							* content_size)))
			return (NULL);
		ft_memmove(maillon->content, (void*)content, content_size);
		maillon->content_size = content_size;
	}
	maillon->next = NULL;
	return (maillon);
}
