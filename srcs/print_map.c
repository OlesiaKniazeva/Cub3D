/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:31:22 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 14:27:49 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	print_map(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (all->m->map[y])
	{
		x = 0;
		while (all->m->map[y][x])
		{
			if (x == (int)all->player->pos_x && y == (int)all->player->pos_y)
			{
				print_pixel_scale(all->player->pos_x, all->player->pos_y, RED, all);
			}
			else if (all->m->map[y][x] == '1')
				print_pixel_scale(x, y, BLUE, all);
			else if (all->m->map[y][x] == '0')
				print_pixel_scale(x, y, WHITE, all);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 3, 3);
}