#include "cub3D.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->l_len + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

// int	check_if_coord_is_player(t_all *all)
// {
// 	t_player *player = all->player;

// 	return (all->m->map[(int)player->posY][(int)player->posX] == 'P');
// }

// int	coordinate_is_zero(t_all *all)
// {
// 	t_player *player = all->player;

// 	return (all->m->map[(int)player->posY][(int)player->posX] == '0');
// }

// int	coordinate_is_one(t_all *all)
// {
// 	t_player *player = all->player;

// 	return (all->m->map[(int)player->posY][(int)player->posX] == '1');
// }

// void	check_coordinate_of_map(t_all *all, int key_code)
// {
// 	if (!check_if_coord_is_player(all) && coordinate_is_zero(all))
// 	{
// 		*all->player->player_on_map = '0';
// 		all->m->map[(int)all->player->posY][(int)all->player->posX] = 'P';
// 		all->player->player_on_map = &all->m->map[(int)all->player->posY][(int)all->player->posX];
// 	}
// 	else if (coordinate_is_one(all))
// 	{
// 		if (key_code == UP)
// 			all->player->posY += 0.3;
// 		else if (key_code == DOWN)
// 			all->player->posY -= 0.3;
// 		else if (key_code == RIGHT)
// 			all->player->posX -= 0.3;
// 		else
// 			all->player->posX += 0.3;
// 	}
// }

// void	change_map(t_all *all, int key_code)
// {
// 	if (key_code == UP)
// 	{
// 		all->player->posY -= 0.3;
// 		check_coordinate_of_map(all, key_code);
// 	}
// 	if (key_code == DOWN)
// 	{
// 		all->player->posY += 0.3;
// 		check_coordinate_of_map(all, key_code);
// 	}
// 	if (key_code == RIGHT)
// 	{
// 		all->player->posX += 0.3;
// 		check_coordinate_of_map(all, key_code);
// 	}
// 	if (key_code == LEFT)
// 	{
// 		all->player->posX -= 0.3;
// 		check_coordinate_of_map(all, key_code);
// 	}
// 	print_double_array(all->m);
// }

void	change_map(t_all *all, int key_code)
{
	double moveSpeed = 0.11;
	double rotSpeed = 0.055;

	if (key_code == W_UP)
	{
		if (all->m->map[(int)all->player->posY][(int)(all->player->posX +
					all->player->dirX * moveSpeed)] == '0')
		{
			all->player->posX += all->player->dirX * moveSpeed;
		}
		if (all->m->map[(int)(all->player->posY + all->player->dirY *
					moveSpeed)][(int)all->player->posX] == '0')
		{
			all->player->posY += all->player->dirY * moveSpeed;
		}
	}
	if (key_code == S_DOWN) {
		if (all->m->map[(int)all->player->posY][(int)(all->player->posX -
				all->player->dirX * moveSpeed)] == '0')
		{
			all->player->posX -= all->player->dirX * moveSpeed;
		}
		if (all->m->map[(int)(all->player->posY - all->player->dirY *
				moveSpeed)][(int)all->player->posX] == '0')
		{
			all->player->posY -= all->player->dirY * moveSpeed;
		}
	}
	if (key_code == D_RIGHT)
	{
		double oldDirX = all->player->dirX;
		all->player->dirX = all->player->dirX * cos(-rotSpeed)
				- all->player->dirY * sin(-rotSpeed);
		all->player->dirY = oldDirX * sin(-rotSpeed) +
				all->player->dirY * cos(-rotSpeed);
		double oldPlaneX = all->plane->planeX;
		all->plane->planeX = all->plane->planeX * cos(-rotSpeed) -
				all->plane->planeY * sin(-rotSpeed);
		all->plane->planeY = oldPlaneX * sin(-rotSpeed) +
				all->plane->planeY * cos(-rotSpeed);
	}
	if (key_code == A_LEFT)
	{
		double oldDirX = all->player->dirX;
		all->player->dirX = all->player->dirX * cos(rotSpeed) -
				all->player->dirY * sin(rotSpeed);
		all->player->dirY = oldDirX * sin(rotSpeed) +
				all->player->dirY * cos(rotSpeed);
		double oldPlaneX = all->plane->planeX;
		all->plane->planeX = all->plane->planeX * cos(rotSpeed) -
				all->plane->planeY * sin(rotSpeed);
		all->plane->planeY = oldPlaneX * sin(rotSpeed) +
				all->plane->planeY * cos(rotSpeed);
	}
}

int	check_if_key_code_arrow(int key_code)
{
	return (key_code == W_UP || key_code == S_DOWN ||
			key_code == A_LEFT || key_code == D_RIGHT);
	// return (key_code == UP || key_code == DOWN ||
	// 		key_code == LEFT || key_code == RIGHT);
}

int	key_hook(int key_code, t_all *all)
{
	if (key_code == ESC)
	{
		free_memory(all);
		exit(0);
	}
	if (check_if_key_code_arrow(key_code))
	{
		change_map(all, key_code);
	// print_double_array(all->m);
	// print_map(all);
	// mlx_destroy_image(all->win->mlx, all->win->img);
	// all->win->img = mlx_new_image(all->win->mlx, all->m->width * 50, all->m->height * 50);
	print_raycaster(all);
	// printf("%d\n", key_code);
	}

	return 0;
}
