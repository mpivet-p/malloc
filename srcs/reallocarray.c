#include "libft_malloc.h"

void	*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	(void)ptr;
	return (calloc(nmemb, size));
}
