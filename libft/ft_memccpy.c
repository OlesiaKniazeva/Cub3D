#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	symbol;

	symbol = c;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n)
	{
		if (*source == symbol)
		{
			*dest = *source;
			dest++;
			return (dest);
		}
		*dest = *source;
		source++;
		dest++;
		n--;
	}
	return (NULL);
}
