#include "libft_malloc.h"
#include <unistd.h>

extern t_page *g_heap;

int		ft_putchar(int c)
{
	return (write(1, &c, 1));	
}

static void rec_hex(uint64_t n)
{
	if (n >= 16)
	{
		rec_hex(n / 16);
		ft_putchar("0123456789abcdef"[(int)(n % 16)]);
	}
	else
	{
		ft_putchar("0123456789abcdef"[(int)n]);
	}

}

void	puthex(uint64_t n)
{
	write(1, "0x", 2);
	rec_hex(n);
	write(1, "\n", 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			n = -147483648;
		}
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
	else
		ft_putchar(n + 48);
}

void	debug_page(t_page *ptr)
{
	t_chunk *chunk = ptr->first_chunk;
	while (chunk)
	{
		puthex((uint64_t)chunk->data);
		chunk = chunk->next;
	}
}

static t_chunk	*find_chunk(t_chunk *chunk, void *ptr)
{
	while (chunk)
	{
		write(1, "W\n\n", 3);
		puthex((uint64_t)chunk);
		write(1, "\n\n", 2);
		puthex((uint64_t)ptr);
		write(1, "\n\n", 2);
		if (chunk->available == FALSE && chunk->data == ptr)
		{
			write(1, "O\n", 2);
			return (chunk);
		}
		write(1, "E\n", 2);
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
		puthex((uint64_t)page_ptr->type);
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
