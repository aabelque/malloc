/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:20:29 by azziz             #+#    #+#             */
/*   Updated: 2021/02/01 19:06:41 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define PROT (PROT_READ | PROT_WRITE)
# define FLGS (MAP_ANON | MAP_PRIVATE)
# define PS getpagesize()
# define SMALL PS
# define TINY PS / 4
# define STRUCT(x) ft_getalign(sizeof(x), 16)
# define TINY_ZONE ((TINY + STRUCT(t_page) + STRUCT(t_block)) * 100)
# define SMALL_ZONE ((SMALL + STRUCT(t_page) + STRUCT(t_block)) * 100)

# include "../libft/include/libft.h"
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>


typedef struct  s_block
{
    short           free;
    size_t          len;
    void            *p;
    struct s_block  *nxt;
    struct s_block  *prv;
}               t_block;

typedef struct  s_page
{
    short           free;
    size_t          rest;
    t_block         *blk;
    struct s_page   *nxt;
}               t_page;

typedef struct  s_malloc
{
    t_page          *tiny;
    t_page          *small;
    t_page          *large;
}               t_malloc;

t_malloc g_lst;

void        ft_free(void *ptr);
void        *ft_malloc(size_t size);
size_t      ft_getalign(size_t size, int align);
t_block     *ft_new_block(size_t size);
void        show_alloc_mem(void);
void        *ft_create_zone(t_page *prev, size_t size, size_t len);
void        *ft_alloc_large(t_page **page, size_t len);
/* void        ft_find_fragment(t_page *page); */
/* void        ft_defrag(t_block **curr, t_block **prev, t_block **next); */
/* void    *realloc(void *ptr, size_t size); */

#endif
