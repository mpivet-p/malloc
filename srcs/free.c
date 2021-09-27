/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:50:35 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/10/03 14:08:57 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <stdio.h>
#include "libft_malloc.h"

extern t_page *g_heap;

void	clean_pages(void)
{
	t_page *ptr = g_heap;
	t_page *prev_page;
	t_page *next_page;

	while (ptr)
	{
		next_page = ptr->next;
		if (ptr->chunks == ptr->chunks_available)
		{
			printk("need munmap for page %p\n", ptr);
			//debug_page(ptr);
			if (ptr == g_heap)
			{
				g_heap = ptr->next;
			}
			else
			{
				prev_page->next = ptr->next;
			}
			munmap((void*)ptr, ptr->size);
			printk("munmap done\n");
		}
		else
		{
			prev_page = ptr;
		}
		ptr = next_page;
	}
}

void	free(void *ptr)
{
	//t_chunk	*chunk;
	//t_page	*page_ptr;

	printk("free(%p)\n", ptr);
	//if ((chunk = get_chunk(ptr, &page_ptr)) != NULL && (page_ptr->type == LARGE_PAGE || page_ptr->type == TINY_PAGE || page_ptr->type == SMALL_PAGE))
	//{
	//	printk("%p %p %p %p\n", ptr, page_ptr, chunk, chunk->data);
	//	chunk->available = TRUE;
	//	chunk->size = 0;
	//	page_ptr->chunks_available += 1;
	//}
	//else
	//{
	//	printk("PTR ERROR %p\n", chunk);
	//}
	//clean_pages();
	printk("== free return ==\n");
}
