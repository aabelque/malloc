/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:00:07 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/17 15:41:47 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *ptr;

	ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s) + 1));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_strcpy(ptr, s);
	return (ptr);
}
