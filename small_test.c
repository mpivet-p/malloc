#include <stdio.h>
#include "libft_malloc.h"

int	main(void)
{
	char *addr;

	addr = (char*)ft_malloc(sizeof(char) * 4);
	printf("addr = %p\n", addr);
	addr = (char*)ft_malloc(sizeof(char) * 42);
	printf("addr = %p\n", addr);
}
