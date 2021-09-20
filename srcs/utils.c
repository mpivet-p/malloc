#include "libft_malloc.h"
#include <unistd.h>

extern t_page *g_heap;

static t_chunk	*find_chunk(t_chunk *chunk, void *ptr)
{
	while (chunk)
	{
		if (chunk->available == FALSE && chunk->data == ptr)
			return (chunk);
		chunk = chunk->next;
	}
	return (NULL);
}

t_chunk *get_chunk(void *ptr, t_page **ret_ptr)
{
	t_page	*page_ptr = g_heap;
	t_chunk	*chunk;
	void	*pg_max;
	void	*pg_min;

	while (page_ptr)
	{
		pg_min = (void*)page_ptr + sizeof(t_page) + (sizeof(t_chunk) * page_ptr->chunks);
		pg_max = (void*)page_ptr + page_ptr->size;
		if (ptr >= pg_min && ptr < pg_max && (chunk = find_chunk(page_ptr->first_chunk, ptr)) != NULL)
		{
			*ret_ptr = page_ptr;
			return (chunk);
		}
		page_ptr = page_ptr->next;
	}
	return (NULL);
}


size_t	get_mempage_size(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_HEAP_SIZE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_HEAP_SIZE);
	return (((size / getpagesize()) + 1) * getpagesize());
}

int		get_page_type(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_PAGE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_PAGE);
	return (LARGE_PAGE);
}
