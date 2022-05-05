#include "cub3D.h"

// void	print_map(t_win *win, t_all *all)
// {
// 	t_plane plane;

// 	plane.planeX = 0;
// 	plane.planeY = 0.66;
// 	double time = 0;
// 	double old_time = 0;
// 	int x = 0;
// 	while (x < all->m->width)
// 	{
// 		double cameraX = 2 * x / (double)all->m->width - 1;
// 		double rayDirX = all->player->dir->dirX + plane.planeX * cameraX;
// 		double rayDirY = all->player->dir->dirY + plane.planeY * cameraX;

// 		int mapX = (int)all->player->dir->dirX;
// 		int mapY = (int)all->player->dir->dirY;

// 		double sideDistX;
// 		double sideDistY;
// 	}
// }

void	print_pixel_scale(int x_c, int y_c, int color, t_all *all)
{
	int scale_f = 10;
	int i = x_c * scale_f;
	int j = y_c * scale_f;
	int x_f = (x_c + 1) * scale_f;
	int y_f = (y_c + 1) * scale_f;

	while (j < y_f)
	{
		i = x_c * scale_f;
		while (i < x_f)
		{
			my_mlx_pixel_put(all->win, i, j, color);
			++i;
		}
		j++;
	}
}

// void	print_player(int color, t_all *all) {
// 	my_mlx_pixel_put(all->win, all->player->x, all->player->y, color);
// }

void	print_map(t_all *all)
{
	int x;
	int y;
	// int i;
	// int j;

	// i = 0;
	// j = 0;

	y = 0;
	while (all->m->map[y])
	{
		x = 0;
		while (all->m->map[y][x])
		{
			if (all->m->map[y][x] == 'P') {
				// print_player(BLUE, all);
				print_pixel_scale(x, y, BLUE, all);
			}
				// print_pixel_scale(x, y, BLUE, all);
			// else if (all->m->map[y][x] == '1')
			// 	print_pixel_scale(x, y, 0xFF000000, win);
			if (all->m->map[y][x] == '1')
				print_pixel_scale(x, y, RED, all);
			if (all->m->map[y][x] == '0')
				print_pixel_scale(x, y, WHITE, all);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
}

void	executing(t_all *all)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, X_SIZE, Y_SIZE, "Cub3D");
	win->img = mlx_new_image(win->mlx, all->m->width * 50, all->m->height * 50);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
		&win->line_length, &win->endian);
	all->win = win;
	print_map(all);
	mlx_key_hook(win->win, key_hook, all);
	mlx_loop(win->mlx);
}