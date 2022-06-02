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

// void print_pixel_scale(int x_c, int y_c, int color, t_all *all)
// {
// 	int scale_f = 10;
// 	int i = x_c * scale_f;
// 	int j = y_c * scale_f;
// 	int x_f = (x_c + 1) * scale_f;
// 	int y_f = (y_c + 1) * scale_f;

// 	while (j < y_f)
// 	{
// 		i = x_c * scale_f;
// 		while (i < x_f)
// 		{
// 			my_mlx_pixel_put(all->win, i, j, color);
// 			++i;
// 		}
// 		j++;
// 	}
// }

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

void	check_malloc_err(char *data, char *message, int num)
{
	if (!data)
		error_exit(message, num);
}

void	img_to_xpm_data_my(t_win *win, char *path, t_win *data)
{
	data->img = mlx_xpm_file_to_image(win->mlx, path, &data->x, &data->y);
	check_malloc_err(data->img, "couldn't alloc texture img", 21);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
			&data->l_len, &data->end);
	check_malloc_err(data->addr, "couldn't alloc texture addr", 22);
}

void init_data_for_textures(t_all *all)
{
	all->s_tex = malloc(sizeof(t_win));
	all->w_tex = malloc(sizeof(t_win));
	all->e_tex = malloc(sizeof(t_win));
	all->n_tex = malloc(sizeof(t_win));
	img_to_xpm_data_my(all->win, all->data->s_texture, all->s_tex);
	img_to_xpm_data_my(all->win, all->data->n_texture, all->n_tex);
	img_to_xpm_data_my(all->win, all->data->e_texture, all->e_tex);
	img_to_xpm_data_my(all->win, all->data->w_texture, all->w_tex);
}

// void printVerticalLine(int x, int drawStart, int drawEnd, t_all *all, int color)
// {
// 	int y = 0;

// 	while (y < HEIGHT)
// 	{
// 		if (y < drawStart)
// 		{
// 			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->ceiling[0], all->data->ceiling[1], all->data->ceiling[2]));
// 		}
// 		else if (y >= drawStart && y <= drawEnd)
// 		{
// 			my_mlx_pixel_put(all->win, x, y, color);
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->floor[0], all->data->floor[1], all->data->floor[2]));
// 		}
// 		++y;
// 	}
// }

unsigned int	get_tex_color_pixel(t_win *img, int x, int y)
{
	int	*dst;
	int	color;

	dst = (void *)img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(int *)dst;
	return (color);
}

// int	add_shade(double distance, int color)
// {
// 	int		transparency;
// 	int		red;
// 	int		green;
// 	int		blue;

// 	transparency = color & 0xFF000000;
// 	red = color & 0x00FF0000;
// 	green = color & 0x0000FF00;
// 	blue = color & 0x000000FF;
// 	red = (red >> 16) * (1 - distance);
// 	green = (green >> 8) * (1 - distance);
// 	blue = blue * (1 - distance);
// 	red = red << 16;
// 	green = green << 8;
// 	return (transparency | red | green | blue);
// }

void	draw_texture(t_all *all, t_win *tex, int x, int shade)
{
	int y;

	y = all->rc->drawStart;
	all->rc->texX = (int)(all->rc->wallX * (double)(tex->x));
	if (all->rc->side == 0 && all->rc->rayDirX > 0)
	{
		all->rc->texX = tex->x - all->rc->texX - 1;
	}
	if (all->rc->side == 1 && all->rc->rayDirY < 0)
	{
		all->rc->texX = tex->x - all->rc->texX - 1;
	}
	all->rc->step = 1.0 * tex->y / all->rc->lineHeight;
	all->rc->texPos = (all->rc->drawStart - HEIGHT / 2 + \
			all->rc->lineHeight / 2) * all->rc->step;
	while (y < all->rc->drawEnd)
	{
		all->rc->texY = (int)all->rc->texPos & (tex->y - 1);
		all->rc->texPos += all->rc->step;
		all->rc->color = get_tex_color_pixel(tex, all->rc->texX, all->rc->texY);
		// if (shade == 0)
		// 	my_mlx_pixel_put(all->win, x, y, all->rc->color);
		// else
		// 	my_mlx_pixel_put(all->win, x, y, add_shade(0.2, all->rc->color));
		if (all->rc->side == 1) {
			all->rc->color = (all->rc->color >> 1) & 8355711;
		}
		(void)shade;
		my_mlx_pixel_put(all->win, x, y, all->rc->color);
		++y;
	}
}

void	draw_textures_on_walls(t_all *all, int x)
{
	if (all->rc->side == 1 && all->rc->stepY < 0)
		draw_texture(all, all->n_tex, x, 1);
	else if (all->rc->side == 1 && all->rc->stepY > 0)
		draw_texture(all, all->s_tex, x, 1);
	else if (all->rc->side == 0 && all->rc->stepX < 0)
		draw_texture(all, all->e_tex, x, 0);
	else if (all->rc->side == 0 && all->rc->stepX > 0)
		draw_texture(all, all->w_tex, x, 0);
}

void	draw_floor_and_ceiling(t_all *all, int x)
{
	int y = 0;

	while (y < HEIGHT)
	{
		if (y <= all->rc->drawStart)
		{
			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->ceiling[0], \
					all->data->ceiling[1], all->data->ceiling[2]));
		}
		else if (y >= all->rc->drawEnd)
		{
			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->floor[0], \
					all->data->floor[1], all->data->floor[2]));
		}
		++y;
	}
}


void	print_raycasted_map(int x, t_all *all)
{
	// int color = BLUE;
	// if (all->rc->side == 1)
	// 	color /= 2;
	// printVerticalLine(x, all->rc->drawStart, all->rc->drawEnd, all, color);

    // texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y); //flat red texture with black cross
    // texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    // texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    // texture[3][TEX_W * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    // texture[4][TEX_W * y + x] = 256 * xorcolor; //xor green
    // texture[5][TEX_W * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    // texture[6][TEX_W * y + x] = 65536 * ycolor; //red gradient
    // texture[7][TEX_W * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture


	// unsigned int texture[TEX_W * TEX_H];
	// 	for (int x = 0; x < TEX_W; ++x)
	// 	{
	// 		for (int y = 0; y < TEX_H; ++y)
	// 		{
	// 			int xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
    // 			// int xcolor = x * 256 / TEX_W;
    // 			// int ycolor = y * 256 / TEX_H;
    // 			// int xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
	// 			 = 256 * xorcolor;
	//			texture[TEX_W * y + x] =  256 * xorcolor;
	// 		}
	// 	}



	if (all->rc->side == 0)
	{
		all->rc->wallX = all->player->posY + all->rc->perpWallDist * \
				all->rc->rayDirY;
	}
	else
	{
		all->rc->wallX = all->player->posX + all->rc->perpWallDist * \
				all->rc->rayDirX;
	}
	all->rc->wallX -= floor((all->rc->wallX));


	draw_textures_on_walls(all, x);
	draw_floor_and_ceiling(all, x);


	// all->rc->texX = (int)(all->rc->wallX * (double)(TEX_W));
	// if (all->rc->side == 0 && all->rc->rayDirX > 0)
	// {
	// 	all->rc->texX = TEX_W - all->rc->texX - 1;
	// }
	// if (all->rc->side == 1 && all->rc->rayDirY < 0)
	// {
	// 	all->rc->texX = TEX_W - all->rc->texX - 1;
	// }

	// all->rc->step = 1.0 * TEX_H / all->rc->lineHeight;

	// all->rc->texPos = (all->rc->drawStart - HEIGHT / 2 + all->rc->lineHeight / 2) * all->rc->step;
	// for (int y = all->rc->drawStart; y < all->rc->drawEnd; ++y)
	// {
	// 	all->rc->texY = (int)all->rc->texPos & (TEX_H - 1);
	// 	all->rc->texPos += all->rc->step;
	// 	all->rc->color = all->data->s_texture_arr[TEX_H * all->rc->texY + all->rc->texX];
	// 	// all->rc->color = texture[TEX_H * all->rc->texY + all->rc->texX];
	// 	// if (all->rc->side == 1)
	// 	// {
	// 	// 	all->rc->color = (all->rc->color >> 1) & 8355711;
	// 	// }
	// 	my_mlx_pixel_put(all->win, x, y, all->rc->color);
	// }
}



void print_raycaster(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	raycaster_start(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);

	// int x = 0;
}

// void	test(t_all *all) {
// 	unsigned int texture[TEX_W * TEX_H];
// 	for (int x = 0; x < TEX_W; ++x) {
// 		for(int y = 0; y < TEX_H; ++y) {
// 			texture[TEX_W * y + x] = 65536 * 192 * (x % 16 && y % 16);
// 		}
// 	}

// 	for (int y = 0; y < TEX_H; ++y) {
// 		for (int x = 0; x < TEX_H; ++x) {
// 			my_mlx_pixel_put(all->win, x, y, texture[TEX_W * y + x]);
// 		}
// 	}
// 	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
// }

void executing(t_all *all)
{
	all->win = malloc(sizeof(t_win));
	all->rc = malloc(sizeof(t_raycast));
	all->win->mlx = mlx_init();
	init_data_for_textures(all);
	all->win->win = mlx_new_window(all->win->mlx, WIDTH, HEIGHT, "Cub3D");
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
								  &all->win->l_len, &all->win->end);

	// test(all);
	// print_map(all);

	print_raycaster(all);

	// mlx_key_hook(win->win, key_hook, all);
	mlx_hook(all->win->win,2 , (1L << 0), key_hook, all);
	// mlx_hook(win->win, 17, 0, &close_win, &data);
	mlx_loop(all->win->mlx);
}