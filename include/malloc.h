/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:20:29 by azziz             #+#    #+#             */
/*   Updated: 2021/02/24 15:34:33 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define PROT (PROT_READ | PROT_WRITE)
# define FLGS (MAP_ANON | MAP_PRIVATE)
# define SMALL 4096
# define TINY 512
# define STRUCT(x) ft_getalign(sizeof(x), 16)
# define TINY_ZONE (TINY * 100)
# define SMALL_ZONE (SMALL * 100)
# define HEAP_SHIFT(start) ((void *)start + STRUCT(t_heap))
# define BLK_SHIFT(start) ((void *)start + STRUCT(t_block))

typedef struct	s_block
{
	short			free;
	size_t			len;
	void			*p;
	struct s_block	*nxt;
	struct s_block	*prv;
}				t_block;

typedef struct	s_heap
{
	short			free;
	size_t			rest;
	size_t			size;
	t_block			*blk;
	struct s_heap	*nxt;
}				t_heap;

typedef struct	s_malloc
{
	t_heap			*tiny;
	t_heap			*small;
	t_heap			*large;
}				t_malloc;

t_malloc			g_lst;

void			*reallocf(void *ptr, size_t size);
void			*calloc(size_t count, size_t size);
void			free(void *ptr);
void			*malloc(size_t size);
size_t			ft_getalign(size_t size, int align);
t_block			*ft_new_block(size_t size);
void			show_alloc_mem(void);
void			*ft_create_zone(t_heap **lst, size_t size, size_t len);
void			*ft_alloc_large(t_heap **heap, size_t len, int sz_struct);
t_block			*ft_init_block(t_block *nw, t_block *blk, size_t len);
void			ft_free_heap(t_heap **zone, int diff);
void			*realloc(void *ptr, size_t size);
t_block			*ft_findblock(t_heap **heap, size_t sz);
void			ft_putchar(char c);
void			ft_putnbr(int n);
size_t			ft_strlen(const char *s);
void			ft_putstr(char const *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_hexdump(long n);

#endif
