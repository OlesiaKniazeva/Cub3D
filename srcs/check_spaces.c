#include "cub3D.h"

void	check_spaces(t_all *all, char **map, int i, int j)
{
	if (check_if_symbol_is_zero_or_player(all, map, i, j - 1) ||
		check_if_symbol_is_zero_or_player(all, map, i, j + 1) ||
		check_if_symbol_is_zero_or_player(all, map, i + 1, j) ||
		check_if_symbol_is_zero_or_player(all, map, i - 1, j) ||
		check_if_symbol_is_zero_or_player(all, map, i + 1, j + 1) ||
		check_if_symbol_is_zero_or_player(all, map, i - 1, j + 1) ||
		check_if_symbol_is_zero_or_player(all, map, i + 1, j - 1) ||
		check_if_symbol_is_zero_or_player(all, map, i - 1, j - 1))
		error_exit("Zero symbol found in wrong place", 16);
}

void	check_line_for_spaces(t_all *all, char **map, int i)
{
	int j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != ' ')
		{
			if (all->checker->space_line == 1)
				error_exit("Space line inside the map", 17);
			return ;
		}
		j++;
	}
	all->checker->space_line = 1;
}