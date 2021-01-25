/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:46:07 by aabelque          #+#    #+#             */
/*   Updated: 2017/11/24 20:31:46 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *buff;

	if (!(buff = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(buff, size + 1);
	return (buff);
}
