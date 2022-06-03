#include "cub3D.h"

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

void init_data_for_textures_and_speed(t_all *all)
{
	all->s_tex = malloc(sizeof(t_win));
	all->w_tex = malloc(sizeof(t_win));
	all->e_tex = malloc(sizeof(t_win));
	all->n_tex = malloc(sizeof(t_win));
	img_to_xpm_data_my(all->win, all->data->s_texture, all->s_tex);
	img_to_xpm_data_my(all->win, all->data->n_texture, all->n_tex);
	img_to_xpm_data_my(all->win, all->data->e_texture, all->e_tex);
	img_to_xpm_data_my(all->win, all->data->w_texture, all->w_tex);
	all->player->moveSpeed = 0.11;
	all->player->rotSpeed = 0.055;
}

unsigned int	get_tex_color_pixel(t_win *img, int x, int y)
{
	int	*dst;
	int	color;

	dst = (void *)img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(int *)dst;
	return (color);
}

int	add_shade(double distance, int color)
{
	int		transparency;
	int		red;
	int		green;
	int		blue;

	transparency = color & 0xFF000000;
	red = color & 0x00FF0000;
	green = color & 0x0000FF00;
	blue = color & 0x000000FF;
	red = (red >> 16) * (1 - distance);
	green = (green >> 8) * (1 - distance);
	blue = blue * (1 - distance);
	red = red << 16;
	green = green << 8;
	return (transparency | red | green | blue);
}

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
		if (shade == 0)
			my_mlx_pixel_put(all->win, x, y, all->rc->color);
		else
			my_mlx_pixel_put(all->win, x, y, add_shade(0.2, all->rc->color));
		++y;
	}
}

void	draw_textures_on_walls(t_all *all, int x)
{
	if (all->rc->side == 1 && all->rc->stepY < 0)
		draw_texture(all, all->n_tex, x, 1);
	else if (all->rc->side == 1 && all->rc->stepY > 0)
		draw_texture(all, all->s_tex, x, 0);
	else if (all->rc->side == 0 && all->rc->stepX < 0)
		draw_texture(all, all->e_tex, x, 1);
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
}

void print_raycaster(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	raycaster_start(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
}

void executing(t_all *all)
{
	all->win = malloc(sizeof(t_win));
	all->rc = malloc(sizeof(t_raycast));
	all->win->mlx = mlx_init();
	init_data_for_textures_and_speed(all);
	all->win->win = mlx_new_window(all->win->mlx, WIDTH, HEIGHT, "Cub3D");
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
								  &all->win->l_len, &all->win->end);
	print_raycaster(all);

	// mlx_key_hook(win->win, key_hook, all);
	mlx_hook(all->win->win,2 , (1L << 0), key_hook, all);
	// mlx_hook(win->win, 17, 0, &close_win, &data);
	mlx_loop(all->win->mlx);
}