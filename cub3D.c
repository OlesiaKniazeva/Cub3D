#include "cub3D.h"

int main(int argc, char **argv)
{
	t_all 	all;
	int		len;

	if (argc != 2)
		error_exit("Wrong amount of arguments", 1);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(".cub", argv[1] + len - 4, 5))
		error_exit("Wrong format of map", 9);
	parse_data(argv, &all);
	// while(1);
	executing(&all);
	free_memory(&all);
}