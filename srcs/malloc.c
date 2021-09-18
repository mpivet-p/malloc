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
#include "libft.h"
#include <stdio.h>

t_page *g_heap = NULL;

void print_page_type(int type)
{
	static char *page_type[] = {"TINY_PAGE", "SMALL_PAGE", "LARGE_PAGE"};	
	printf("Requested %s\n", page_type[type]);
}

static void	*get_available_chunk(t_page *heap, size_t size, t_chunk **ret_chunk)
{
	size_t	page_type;
	t_chunk *chunk;

	page_type = get_page_type(size);
	while (heap)
	{
		if (heap->type == page_type && heap->chunks_available > 0)
		{
			////printf("Page found at %p\n", heap);
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
	void*	alloc_zone_start = (void*)page_ptr + sizeof(t_page) + (sizeof(t_chunk) * chunks_nbr);
	size_t	chunk_size = (page_ptr->type == TINY_PAGE) ? TINY_CHUNK_SIZE : SMALL_CHUNK_SIZE;
	t_chunk	*ptr;

	ptr = (t_chunk*)(page_ptr + sizeof(t_page));
	for (size_t i = 0; i < chunks_nbr - 1; i++)
	{
		ptr[i] = (t_chunk){&(ptr[i + 1]), alloc_zone_start + (chunk_size * i), TRUE, 4242, 0};
	}
	ptr[chunks_nbr - 1] = (t_chunk){NULL, alloc_zone_start + (chunk_size * (chunks_nbr - 1)), TRUE, 4242, 0};
	if (chunks_nbr == 1)
		ptr->data += 8;
}

static void append_heap_ptr(t_page **heap, t_page *page_ptr)
{
	t_page	*ptr = NULL;

	if (*heap == NULL)
	{
		////printf("main heap initialized: %p\n", page_ptr);
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
	else // page_type == LARGE_PAGE
	{
		*page_ptr = (t_page){NULL, first_chunk, page_size, 1, 1, LARGE_PAGE, 4242, ""};
		init_chunks(page_ptr, 1);
	}
	////print_page_type(page_ptr->type);
	append_heap_ptr(heap, page_ptr);
	return (page_ptr);
}

static void	*get_mem_page(t_page **heap, size_t size)
{
	size_t	heap_size;
	void	*ptr;

	heap_size = get_page_size(size);
	if ((ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (set_new_page(heap, (t_page*)ptr, heap_size, size));
}

static void	*alloc_chunk(t_page *heap, t_chunk *chunk)
{
	heap->chunks_available--;
	chunk->available = FALSE;
	return (chunk->data);
}

void		*ft_malloc(size_t size)
{
	t_page			*alloc_heap = NULL;
	t_chunk			*chunk = NULL;

  	////write(1, "=========[ NEW.MALLOC.CALL ]=========\n", 38);
	////printf("requested %zu bytes to malloc\n", size);
	if (size > 0)
	{
		////printf("checking if a page contains enough space...\n");
		if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
		{
			////printf("Not enough space, calling mmap...\n");
			if (get_mem_page(&g_heap, size) == NULL)
			{
				////printf("mmap failed, returning NULL\n");
				return (NULL);
			}
			if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
			{
				////printf("Still not enough memory, returning NULL\n");
				return (NULL);
			}
		}
		return (alloc_chunk(alloc_heap, chunk));
	}
	return (NULL);
}
