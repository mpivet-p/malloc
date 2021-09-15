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

static size_t	get_page_size(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_HEAP_SIZE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_HEAP_SIZE);
	return ((size / PAGE_SIZE) + 1);
}

static size_t	get_page_type(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_PAGE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_PAGE);
	return (LARGE_PAGE);
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
			printf("Page found at %p\n", heap);
			chunk = heap->first_chunk;
			while (chunk && chunk->available != TRUE)
			{
				chunk = chunk->next;
			}
			if (chunk && chunk->available == TRUE)
			{
				*ret_chunk = chunk;
				return (heap);
			}
		}
		heap = heap->next;
	}
	return (NULL);
}

static void init_chunks(t_page *page_ptr)
{
	t_chunk *ptr;

	ptr = (t_chunk*)(page_ptr + sizeof(t_page));
	for (size_t i = 0; i < 99; i++)
	{
		ptr[i] = (t_chunk){&(ptr[i + 1]), page_ptr + ALLOC_ZONE_START + (sizeof(t_chunk) * i), TRUE, ""};
	}
	ptr[99] = (t_chunk){NULL, page_ptr + ALLOC_ZONE_START + (sizeof(t_chunk) * 99), TRUE, ""};
}

static void *set_new_page(t_page **heap, t_page *page_ptr, size_t page_size, size_t alloc_size)
{
	t_page *ptr = NULL;

	*page_ptr = (t_page){NULL, (t_chunk*)(page_ptr + sizeof(t_page)), page_size, 100, 100, get_page_type(alloc_size), ""};
	if (alloc_size <= SMALL_CHUNK_SIZE)
		init_chunks(page_ptr);
	if (*heap == NULL)
	{
		printf("main heap initialized: %p\n", page_ptr);
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
	return (page_ptr);
}

static void	*get_mem_page(t_page **heap, size_t size)
{
	size_t	heap_size;
	void	*ptr;

	heap_size = get_page_size(size);
	if ((ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	return(set_new_page(heap, (t_page*)ptr, heap_size, size));
}

static void	*alloc_chunk(t_page *heap, size_t size, t_chunk *chunk)
{
	printf("Allocating a block of size : %lu\n", size);
	heap->chunks_available--;
	chunk->available = FALSE;
	return (chunk->data);
}

void		*ft_malloc(size_t size)
{
	t_page			*alloc_heap = NULL;
	t_chunk			*chunk = NULL;

  	write(1, "=========[ NEW.MALLOC.CALL ]=========\n", 38);
	if (size > 0)
	{
		printf("checking if a page contains enough space...\n");
		if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
		{
			printf("Not enough space, calling mmap...\n");
			if (get_mem_page(&g_heap, size) == NULL)
					
			{
				printf("mmap failed, returning NULL\n");
				return (NULL);
			}
			if ((alloc_heap = get_available_chunk(g_heap, size, &chunk)) == NULL)
			{
				printf("Still not enough memory, returning NULL\n");
				return (NULL);
			}
		}
		return (alloc_chunk(alloc_heap, size, chunk));
	}
	return (NULL);
}
