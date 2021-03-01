/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:37 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/01 17:24:09 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

inline void				ft_hexdump(long n)
{
	if (n > 15)
		ft_hexdump(n / 16);
	if (n % 16 < 10)
		ft_putchar((n % 16) + 48);
	else
		ft_putchar((n % 16) - 10 + 97);
}

static inline void		print_mem_large(t_heap *heap, int *i)
{
	t_heap	*head;

	ft_hexdump((long)heap);
	write(1, "\n", 1);
	head = heap;
	while (heap)
	{
		write(1, "0X", 2);
		ft_hexdump((long)HEAP_SHIFT(heap));
		ft_putstr(" - ");
		write(1, "0X", 2);
		ft_hexdump((long)heap->nxt);
		ft_putstr(" : ");
		ft_putnbr(heap->size);
		ft_putstr(" octets\n");
		*i += heap->size;
		heap = heap->nxt;
	}
	heap = head;
}

static inline void		print_mem(t_heap *blk)
{
	write(1, "0X", 2);
	ft_hexdump((long)HEAP_SHIFT(blk));
	ft_putstr(" - ");
	write(1, "0X", 2);
	ft_hexdump((long)blk->nxt);
	ft_putstr(" : ");
	ft_putnbr(blk->size);
	ft_putstr(" octets\n");
}

static inline void		search_mem(t_heap *heap, int *i)
{
	t_heap	*head;

	ft_hexdump((long)heap);
	write(1, "\n", 1);
	head = heap;
	while (heap)
	{
		if (!heap->free)
		{
			print_mem(heap);
			*i += heap->size;
		}
		heap = heap->nxt;
		write(1, "\n", 1);
	}
	heap = head;
}

void					show_alloc_mem(void)
{
	int		i;
	t_heap	*tiny;
	t_heap	*small;
	t_heap	*large;

	i = 0;
	tiny = g_lst.tiny;
	small = g_lst.small;
	large = g_lst.large;
	ft_putstr("TINY : ");
	search_mem(tiny, &i);
	write(1, "\n", 1);
	ft_putstr("SMALL : ");
	search_mem(small, &i);
	write(1, "\n", 1);
	ft_putstr("LARGE : ");
	print_mem_large(large, &i);
	write(1, "\n", 1);
	ft_putstr("Total : ");
	ft_putnbr(i);
	ft_putstr(" octets\n");
}
