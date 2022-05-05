#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*new;
	int		a;

	a = ft_strlen(s);
	while (a >= 0)
	{
		if (*(s + a) == c)
		{
			new = (char *)(s + a);
			return (new);
		}
		a--;
	}
	new = 0;
	return (new);
}
