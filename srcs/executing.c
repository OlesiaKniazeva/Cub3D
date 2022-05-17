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
// 		double rayDirX = all->player->dirX + plane.planeX * cameraX;
// 		double rayDirY = all->player->dirY + plane.planeY * cameraX;

// 		int mapX = (int)all->player->dirX;
// 		int mapY = (int)all->player->dirY;

// 		double sideDistX;
// 		double sideDistY;
// 	}
// }

void print_pixel_scale(int x_c, int y_c, int color, t_all *all)
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

// void	print_map(t_all *all)
// {
// 	int x;
// 	int y;
// 	// int i;
// 	// int j;

// 	// i = 0;
// 	// j = 0;

// 	y = 0;
// 	while (all->m->map[y])
// 	{
// 		x = 0;
// 		while (all->m->map[y][x])
// 		{
// 			if (all->m->map[y][x] == 'P')
// 			{
// 				// print_player(BLUE, all);
// 				print_pixel_scale(x, y, BLUE, all);
// 			}
// 			// print_pixel_scale(x, y, BLUE, all);
// 			// else if (all->m->map[y][x] == '1')
// 			// 	print_pixel_scale(x, y, 0xFF000000, win);
// 			if (all->m->map[y][x] == '1')
// 				print_pixel_scale(x, y, RED, all);
// 			if (all->m->map[y][x] == '0')
// 				print_pixel_scale(x, y, WHITE, all);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
// }

// void init_data_for_execution(t_all *all)
// {
// 	t_plane *plane;
// 	t_time *time;

// 	time = malloc(sizeof(t_time));
// 	plane = malloc(sizeof(t_plane));
// 	if (all->player->dirX == 0 &&
// 		(all->player->dirY == 1 || all->player->dirY == -1))
// 	{
// 		plane->planeX = 0.66;
// 		plane->planeY = 0;
// 	}
// 	if (all->player->dirY == 0 &&
// 		(all->player->dirX == 1 || all->player->dirX == -1))
// 	{
// 		plane->planeX = 0;
// 		plane->planeY = 0.66;
// 	}
// 	all->plane = plane;
// 	time->old_time = 0;
// 	time->time = 0;
// 	all->time = time;
// }

void printVerticalLine(int x, int drawStart, int drawEnd, t_all *all)
{
	int y = 0;

	while (y < HEIGHT)
	{
		if (y < drawStart)
		{
			my_mlx_pixel_put(all->win, x, y, CYAN);
		}
		else if (y >= drawStart && y <= drawEnd)
		{
			my_mlx_pixel_put(all->win, x, y, RED);
		}
		else
		{
			my_mlx_pixel_put(all->win, x, y, WHITE);
		}
		++y;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
}

void print_raycaster(t_all *all)
{
	int x = 0;

	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = all->player->dirX + all->plane->planeX * cameraX;
		double rayDirY = all->player->dirY + all->plane->planeY * cameraX;

		int mapX = (int)(all->player->posX);
		int mapY = (int)(all->player->posY);

		double sideDistX;
		double sideDistY;

		double deltaDistX;
		double deltaDistY;

		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (all->player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - all->player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (all->player->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - all->player->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (all->m->map[mapY][mapX] == '1')
				hit = 1;

			if (side == 0)
			{
				perpWallDist = sideDistX - deltaDistX;
			}
			else
			{
				perpWallDist = sideDistY - deltaDistY;
			}

			int lineHeight = (int)(HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + HEIGHT / 2;
			if (drawStart < 0)
			{
				drawStart = 0;
			}
			int drawEnd = lineHeight / 2 + HEIGHT / 2;
			if (drawEnd >= HEIGHT)
			{
				drawEnd = HEIGHT - 1;
			}

			int color = BLUE;
			if (side == 1)
			{
				color /= 2;
			}
			printVerticalLine(x, drawStart, drawEnd, all);
		}
		++x;
	}
}

void executing(t_all *all)
{
	t_win *win;

	// init_data_for_execution(all);
	win = malloc(sizeof(t_win));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "Cub3D");
	win->img = mlx_new_image(win->mlx, all->m->width * 50, all->m->height * 50);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
								  &win->line_length, &win->endian);
	all->win = win;
	// print_map(all);
	print_raycaster(all);
	mlx_key_hook(win->win, key_hook, all);
	mlx_loop(win->mlx);
}