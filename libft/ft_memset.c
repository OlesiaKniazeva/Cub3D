#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	symbol;
	char			*str;

	str = (char *)b;
	symbol = c;
	while (len)
	{
		*str = symbol;
		str++;
		len--;
	}
	return (b);
}
