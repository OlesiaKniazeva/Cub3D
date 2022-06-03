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

void	move_player_right_left(t_all *all, int key_code, double moveSpeed)
{
	if (key_code == A_LEFT)
	{
		if ((all->m->map[(int)all->player->posY][(int)(all->player->posX - \
					all->plane->planeX * moveSpeed)] == '0'))
			all->player->posX -= all->plane->planeX * moveSpeed;
		if (all->m->map[(int)(all->player->posY - all->plane->planeY * \
					moveSpeed)][(int)all->player->posX] == '0')
			all->player->posY -= all->plane->planeY * moveSpeed;
	}
	if (key_code == D_RIGHT)
	{
		if ((all->m->map[(int)all->player->posY][(int)(all->player->posX + \
					all->plane->planeX * moveSpeed)] == '0'))
			all->player->posX += all->plane->planeX * moveSpeed;
		if (all->m->map[(int)(all->player->posY + all->plane->planeY * \
					moveSpeed)][(int)all->player->posX] == '0')
			all->player->posY += all->plane->planeY * moveSpeed;
	}
}

void	move_player_up_down(t_all *all, int key_code, double moveSpeed)
{
	if (key_code == W_UP)
	{
		if (all->m->map[(int)all->player->posY][(int)(all->player->posX + \
					all->player->dirX * moveSpeed)] == '0')
			all->player->posX += all->player->dirX * moveSpeed;
		if (all->m->map[(int)(all->player->posY + all->player->dirY * \
					moveSpeed)][(int)all->player->posX] == '0')
			all->player->posY += all->player->dirY * moveSpeed;
	}
	if (key_code == S_DOWN) {
		if (all->m->map[(int)all->player->posY][(int)(all->player->posX - \
				all->player->dirX * moveSpeed)] == '0')
			all->player->posX -= all->player->dirX * moveSpeed;
		if (all->m->map[(int)(all->player->posY - all->player->dirY * \
				moveSpeed)][(int)all->player->posX] == '0')
			all->player->posY -= all->player->dirY * moveSpeed;
	}
}

void	rotate_player_view(t_all *all, double rotSpeed)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = all->player->dirX;
	all->player->dirX = all->player->dirX * cos(rotSpeed) -
			all->player->dirY * sin(rotSpeed);
	all->player->dirY = oldDirX * sin(rotSpeed) +
			all->player->dirY * cos(rotSpeed);
	oldPlaneX = all->plane->planeX;
	all->plane->planeX = all->plane->planeX * cos(rotSpeed) -
			all->plane->planeY * sin(rotSpeed);
	all->plane->planeY = oldPlaneX * sin(rotSpeed) +
			all->plane->planeY * cos(rotSpeed);
}

int	key_hook(int key_code, t_all *all)
{
	// printf("%d\n", key_code);
	if (key_code == ESC)
	{
		free_memory(all);
		exit(0);
	}
	if (key_code == W_UP || key_code == S_DOWN)
		move_player_up_down(all, key_code, all->player->moveSpeed);
	if (key_code == A_LEFT || key_code == D_RIGHT)
		move_player_right_left(all, key_code, all->player->moveSpeed);
	if (key_code == RIGHT)
		rotate_player_view(all, -all->player->rotSpeed);
	if (key_code == LEFT)
		rotate_player_view(all, all->player->rotSpeed);
	print_raycaster(all);
	return 0;
}
