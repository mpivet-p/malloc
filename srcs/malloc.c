/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:52:51 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/10/04 16:39:36 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft_malloc.h"
#include <stdio.h>

t_page *g_heap = NULL;

static void	*get_available_chunk(t_page *heap, size_t size, t_chunk **ret_chunk)
{
	size_t	page_type;
	t_chunk *chunk;

	page_type = get_page_type(size);
	while (heap)
	{
		if (heap->type == page_type && heap->chunks_available > 0)
		{
			chunk = heap->first_chunk;
			while (chunk)
			{
				if (chunk->available == TRUE)
				{
					*ret_chunk = chunk;
					return (heap);
				}
				chunk = chunk->next;
			}
		}
		heap = heap->next;
	}
	return (NULL);
}

static void init_chunks(t_page *page_ptr, size_t chunks_nbr)
{
	static size_t	chunk_types_size[3] = {TINY_CHUNK_SIZE, SMALL_CHUNK_SIZE, 42};
	t_chunk			*ptr;
	size_t			chunk_size = chunk_types_size[page_ptr->type];
	void			*alloc_zone_start = (void*)page_ptr + sizeof(t_page) + (sizeof(t_chunk) * chunks_nbr);

	ptr = (t_chunk*)(page_ptr + sizeof(t_page));
	write(1, "==========\n", 11);
	puthex((uint64_t)page_ptr);
	for (size_t i = 0; i < chunks_nbr - 1; i++)
	{
		ptr[i] = (t_chunk){ptr + i + 1, alloc_zone_start + (chunk_size * i), chunk_size, TRUE, ""};
		ft_putnbr(i);
		write(1, "\n", 1);
		puthex((uint64_t)(&ptr[i]));
		puthex((uint64_t)(ptr[i].data));
		write(1, "\n", 1);
	}
	ptr[chunks_nbr - 1] = (t_chunk){NULL, alloc_zone_start + (chunk_size * (chunks_nbr - 1)), chunk_size, TRUE, ""};
}

static void append_heap_ptr(t_page **heap, t_page *page_ptr)
{
	t_page	*ptr = NULL;

	if (*heap == NULL)
	{
		*heap = page_ptr;
	}
	else
	{
		ptr = *heap;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = page_ptr;
	}
}

static void *set_new_page(t_page **heap, t_page *page_ptr, size_t page_size, size_t alloc_size)
{
	t_chunk	*first_chunk = (t_chunk*)(page_ptr + sizeof(t_page));
	int		page_type = get_page_type(alloc_size);

	if (page_type == TINY_PAGE || page_type == SMALL_PAGE)
	{
		*page_ptr = (t_page){NULL, first_chunk, page_size, 100, 100, page_type, 4242, ""};
		init_chunks(page_ptr, 100);
	}
	else
	{
		*page_ptr = (t_page){NULL, first_chunk, page_size, 1, 1, LARGE_PAGE, 4242, ""};
		init_chunks(page_ptr, 1);
	}
	append_heap_ptr(heap, page_ptr);
	return (page_ptr);
}

static void	*get_mem_page(t_page **heap, size_t size)
{
	size_t	heap_size;
	void	*ptr;

	heap_size = get_mempage_size(size);
	if ((ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (set_new_page(heap, (t_page*)ptr, heap_size, size));
}

static void	*alloc_chunk(t_page *heap, t_chunk *chunk, size_t size)
{
	heap->chunks_available--;
	chunk->available = FALSE;
	chunk->size = size;
	return (chunk->data);
}

void		*malloc(size_t size)
{
	t_page			*alloc_heap = NULL;
	t_chunk			*chunk = NULL;
	//tmp
	void			*tmp;

	printk("malloc(%d) %p\n", size, g_heap);
	if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
	{
		write(1, "new_page\n", 9);
		if (get_mem_page(&g_heap, size) == NULL)
		{
			return (NULL);
		}
		if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
		{
			return (NULL);
		}
	}
	tmp = alloc_chunk(alloc_heap, chunk, size);
	ft_putnbr((((t_page*)alloc_heap)->chunks_available));
	write(1, "\n", 1);
	puthex((uint64_t)chunk);
	puthex((uint64_t)(chunk->data));
	//puthex((uint64_t)tmp);
	write(1, "\nreturn\n\n", 9);
	return (tmp);
}
