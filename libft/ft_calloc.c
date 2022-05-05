#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	void	*temp;

	pointer = malloc((count) * size);
	if (pointer == NULL)
		return (NULL);
	temp = pointer;
	ft_memset(pointer, 0, (size * count));
	return (temp);
}
