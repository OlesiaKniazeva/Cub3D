#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp;
	char	*source;

	temp = (char *) dst;
	source = (char *) src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n)
	{
		*temp = *source;
		source++;
		temp++;
		n--;
	}
	return (dst);
}
