/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:37:31 by aabelque          #+#    #+#             */
/*   Updated: 2021/01/22 19:59:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "malloc.h" */
#include "../include/malloc.h"

size_t  ft_getalign(size_t size, int align)
{
    return ((size % align) ? size + (align - (size % align)) : size);
}

t_block    *ft_new_block(size_t size)
{
    t_block *new;

    if (!(new = mmap(0, size, PROT, FLGS, -1, 0)))
        return NULL;
    write(1, "X", 1);
    write(1, "\n", 1);
    write(1, "0x", 2);
    ft_putstr(ft_lltoa_base((long long)new, 16));
    write(1, "\n", 1);
    printf("addr printf: %p\n", new);
    write(1, "X", 1);
    write(1, "\n", 1);
    return (new);
}
