#include "libft.h"

char	*ft_strchr_g(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}
