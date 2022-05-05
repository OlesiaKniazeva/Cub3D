#include "cub3D.h"

void error_exit(char *str, int num) {
	printf("Error:\n     %s", str);
	exit(num);
}

void print_double_array(t_map *m)
{
	char **map;

	map = m->map;

	while (*map)
	{
		printf("%s\n", *map);
		map++;
	}
}

char	*ft_spaces_str(int width, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (width - len + 1));
	while (i < width - len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return str;
}