#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*string;
	void		*new;
	char		d;

	d = c;
	string = (char *)s;
	while (n)
	{
		if (*string == d)
		{
			new = (void *)string;
			return (new);
		}
		string++;
		n--;
	}
	return (NULL);
}
