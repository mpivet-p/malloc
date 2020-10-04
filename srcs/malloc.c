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

static void	*get_free_block(t_page *heap, size_t size)
{
	t_block	*block;

	block = (t_block*)(heap + sizeof(t_page));
	while (block != NULL)
	{
		if (block->freed == TRUE
				&& block->size >= size + sizeof(t_block))
			return ((void*)block);
		block = block->next;
	}
	return (NULL);
}

static void	*is_enough_mem(t_page *heap, size_t size)
{
	size_t	min_heap_size;
	t_block	*block;

	if (size <= TINY_BLOCK_SIZE)
		min_heap_size = TINY_HEAP_SIZE;
	else if (size <= SMALL_BLOCK_SIZE)
		min_heap_size = TINY_HEAP_SIZE;
	while (heap != NULL)
	{
		printf("page address : %p page size : %lu  block avalaible %d\n", heap, heap->size, heap->block_available);
		if (heap->size == min_heap_size && heap->block_available == TRUE
				&& (block = get_free_block(heap, size)) != NULL)
			return (block);
		heap = heap->next;
	}
	return (NULL);
}

/*
**	SEGV : block ptr is not modified (block = null)
*/

static void	*get_new_heap(t_page **heap, t_page *ptr, size_t heap_size)
{
	t_block	*new_block;

	printf("heap page address is : %p\n", ptr);
	ptr->next = NULL;
	ptr->first_block = (t_block*)(ptr + sizeof(t_page));
	ptr->size = heap_size;
	ptr->blocks = 0;
	ptr->block_available = 1;
	new_block = (t_block*)(ptr + sizeof(t_page));
	new_block->size = heap_size - sizeof(t_page) - sizeof(t_block);
	new_block->freed = TRUE;
	new_block->next = NULL;
	if (*heap != NULL)
	{
		while ((*heap)->next != NULL)
			*heap = (*heap)->next;
		(*heap)->next = ptr;
	}
	else
		(*heap) = ptr;
	return (ptr);
}

static void	*get_mem_page(t_page **heap, size_t size)
{
	size_t	heap_size;
	void	*ptr;

	if (size <= TINY_BLOCK_SIZE)
		heap_size = TINY_HEAP_SIZE;
	else if (size <= SMALL_BLOCK_SIZE)
		heap_size = SMALL_HEAP_SIZE;
	else
		heap_size = (size / PAGE_SIZE) + 1;
	ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE
			, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return(get_new_heap(heap, (t_page*)ptr, heap_size));
}

static void	*alloc_block(t_block *block, size_t size)
{
	t_block	new_block;

	printf("Allocating a block of size : %lu", size);
	new_block.size = block->size - (size + sizeof(t_block));
	new_block.next = block->next;
	block->next = block + sizeof(t_block) + size;
	block->size = size;
	ft_memcpy(block + sizeof(t_block), &new_block, sizeof(t_block));
	return (block + sizeof(t_block));
}

void		*ft_malloc(size_t size)
{
	static t_page	*heap;
	t_block			*block;

	printf("\n=========[ NEW.MALLOC.CALL ] =========\n");
	if (size > 0)
	{
		printf("size = %lu, checking if a page contains enough space...\n", size);
		if ((block = is_enough_mem(heap, size)) == NULL)
		{
			printf("Not enough space, requesting new mem page to mmap...\n");
			if (get_mem_page(&heap, size) == NULL)
					
			{
				printf("mmap failed, returning NULL\n");
				return (NULL);
			}
			printf("main heap : %p\n", heap);
			if ((block = is_enough_mem(heap, size)) == NULL)
			{
				printf("Still not enough memory\n");
				return (NULL);
			}
		}
		return (alloc_block(block, size));
	}
	printf("size(%lu) <= 0 \n", size);
	return (NULL);
}
