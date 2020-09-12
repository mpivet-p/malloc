#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include <stddef.h>

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif
