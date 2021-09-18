#include <stdio.h>
#include <stdlib.h>

#include "libft_malloc.h"

int	main(void)
{
	char *addr1;
	char *addr2;

	addr1 = (char*)ft_malloc(sizeof(char) * 65);
	ft_free(addr1);
}
