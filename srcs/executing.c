/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:43:44 by myael             #+#    #+#             */
/*   Updated: 2022/06/07 20:38:59 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_all *all, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < all->rc->draw_start)
		{
			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->ceiling[0], \
					all->data->ceiling[1], all->data->ceiling[2]));
		}
		else if (y >= all->rc->draw_end)
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
		all->rc->wall_x = all->player->pos_y + all->rc->perp_wall_dist * \
				all->rc->ray_dir_y;
	}
	else
	{
		all->rc->wall_x = all->player->pos_x + all->rc->perp_wall_dist * \
				all->rc->ray_dir_x;
	}
	all->rc->wall_x -= floor((all->rc->wall_x));
	draw_textures_on_walls(all, x);
	draw_floor_and_ceiling(all, x);
}

void	print_raycaster(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	raycaster_start(all);
}
/*
int	key_for_mac(int keycode, t_all *keys)
{
	if (keycode == 53)
	{
		mlx_destroy_image(keys->win->mlx, keys->win->img);
		mlx_destroy_window(keys->win->mlx, keys->win->img);
		free(keys->win->mlx);
		exit(1);
	}
	if (keycode == 123)
		move_player_up_down(keys, keycode, keys->player->move_speed);
	if (keycode == 124)
		move_player_up_down(keys, keycode, keys->player->move_speed);
	if (keycode == 126)
		move_player_up_down(keys, keycode, keys->player->move_speed);
	if (keycode == 125)
		move_player_up_down(keys, keycode, keys->player->move_speed);
	return (0);
}*/

void	executing(t_all *all)
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
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
	mlx_hook(all->win->win, 2, (1L << 0), key_hook, all);
	mlx_hook(all->win->win, 17, (1L << 0), close_win, all);
	mlx_loop(all->win->mlx);
}
