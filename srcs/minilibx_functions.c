#include "cub3D.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	check_if_coord_is_player(t_all *all)
{
	t_player *player = all->player;

	return (all->m->map[(int)player->y][(int)player->x] == 'P');
}

int	coordinate_is_zero(t_all *all)
{
	t_player *player = all->player;

	return (all->m->map[(int)player->y][(int)player->x] == '0');
}

int	coordinate_is_one(t_all *all)
{
	t_player *player = all->player;

	return (all->m->map[(int)player->y][(int)player->x] == '1');
}

void	check_coordinate_of_map(t_all *all, int key_code)
{
	if (!check_if_coord_is_player(all) && coordinate_is_zero(all))
	{
		*all->player->player_on_map = '0';
		all->m->map[(int)all->player->y][(int)all->player->x] = 'P';
		all->player->player_on_map = &all->m->map[(int)all->player->y][(int)all->player->x];
	}
	else if (coordinate_is_one(all))
	{
		if (key_code == UP)
			all->player->y += 0.3;
		else if (key_code == DOWN)
			all->player->y -= 0.3;
		else if (key_code == RIGHT)
			all->player->x -= 0.3;
		else
			all->player->x += 0.3;
	}
}

void	change_map(t_all *all, int key_code)
{
	if (key_code == UP)
	{
		all->player->y -= 0.3;
		check_coordinate_of_map(all, key_code);
	}
	if (key_code == DOWN)
	{
		all->player->y += 0.3;
		check_coordinate_of_map(all, key_code);
	}
	if (key_code == RIGHT)
	{
		all->player->x += 0.3;
		check_coordinate_of_map(all, key_code);
	}
	if (key_code == LEFT)
	{
		all->player->x -= 0.3;
		check_coordinate_of_map(all, key_code);
	}
	print_double_array(all->m);
}

int	check_if_key_code_arrow(int key_code)
{
	return (key_code == UP || key_code == DOWN ||
			key_code == LEFT || key_code == RIGHT);
}

int	key_hook(int key_code, t_all *all)
{
	if (key_code == ESC)
	{
		free_memory(all);
		exit(0);
	}
	if (check_if_key_code_arrow(key_code))
		change_map(all, key_code);
	// print_double_array(all->m);
	print_map(all);
	// printf("%d\n", key_code);
	return 0;
}
