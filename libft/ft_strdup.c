#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	char	*pointer;

	pointer = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (pointer == NULL)
		return (NULL);
	temp = pointer;
	while (*s1)
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	*temp = '\0';
	return (pointer);
}
