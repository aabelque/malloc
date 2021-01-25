/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_unumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 17:27:44 by aabelque          #+#    #+#             */
/*   Updated: 2020/03/14 18:11:54 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int        ft_len_unumber(unsigned int n)
{
    int    cnt;

    cnt = 0;
    if (n == 0)
        return (1);
    while (n > 0)
    {
        n /= 10;
        cnt++;
    }
    return (cnt);
}
