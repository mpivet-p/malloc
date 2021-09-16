#include "libft_malloc.h"

size_t	get_page_size(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_HEAP_SIZE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_HEAP_SIZE);
	return ((size / PAGE_SIZE) + 1);
}

int		get_page_type(size_t size)
{
	if (size <= TINY_CHUNK_SIZE)
		return (TINY_PAGE);
	else if (size <= SMALL_CHUNK_SIZE)
		return (SMALL_PAGE);
	return (LARGE_PAGE);
}
