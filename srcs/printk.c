#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define PRINT_BUFF_SIZE 2048

int		ft_putchar_buf(int c, char *buffer, size_t *n)
{
	buffer[*n] = c;
	buffer[*n + 1] = 0;
	(*n)++;
	if (*n == PRINT_BUFF_SIZE)
	{
		write(1, buffer, PRINT_BUFF_SIZE);
		*n = 0;
	}
	return (c);
}

static size_t	ft_putstr_buf(char *dst, const char *src, size_t *c)
{
	for (size_t i = 0; src[i] != 0; i++)
	{
		ft_putchar_buf(src[i], dst, c);
	}
	return (*c);
}

static void	ft_itoa_buf(int nbr, char *buffer, size_t *c)
{
	if (nbr < 0)
	{
		ft_putchar_buf('-', buffer, c);
		if (nbr & 0xFFFFFFFF)
		{
			ft_putchar_buf('2', buffer, c);
			nbr = -147483648;
		}
		nbr *= -1;
	}
	if (nbr >= 10)
	{
		ft_itoa_buf(nbr / 10, buffer, c);
		ft_putchar_buf(nbr % 10 + 48, buffer, c);
		return ;
	}
	ft_putchar_buf(nbr + 48, buffer, c);
}

static void	ft_puthex_buf(uint64_t nbr, char *buffer, size_t *c)
{
	if (nbr >= 16)
	{
		ft_puthex_buf(nbr / 16, buffer, c);
		ft_putchar_buf("0123456789abcdef"[nbr % 16], buffer, c);
		return ;
	}
	ft_putchar_buf("0123456789abcdef"[nbr], buffer, c);
}

static void	convert(va_list params_infos, char flag, char *buffer, size_t *c)
{
	switch (flag)
	{
		case 's':
		{
			const char *str = (const char*)va_arg(params_infos, const char*);
			*c = ft_putstr_buf(buffer, str, c);
			break ;
		}
		case 'p':
		{
			void *ptr = (void*)va_arg(params_infos, void*);
			ft_putstr_buf(buffer, "0x", c);
			ft_puthex_buf((uint64_t)ptr, buffer, c);
			break ;
		}
		case 'd':
		{
			int nbr = (int)va_arg(params_infos, int);
			ft_itoa_buf(nbr, buffer, c);
			break ;
		}
		case 'u':
		{
			uint64_t nbr = (uint64_t)va_arg(params_infos, uint64_t);
			(void)nbr;
			break ;
		}
	}
}

int	printk(const char * format, ...)
{
	va_list	params_infos;
	size_t	c = 0;
	char	buffer[PRINT_BUFF_SIZE + 1];

	if (!format)
		return (0);
	va_start(params_infos, format);
	for (size_t i = 0; format[i] != 0; i++)
	{
		if (format[i] == '%' && format[i + 1] != 0)
		{
			i++;
			convert(params_infos, format[i], buffer, &c);
		}
		else
		{
			ft_putchar_buf(format[i], buffer, &c);
		}
	}
	if (c != 0)
		write(1, buffer, c);
	va_end(params_infos);
	return (c);
}
