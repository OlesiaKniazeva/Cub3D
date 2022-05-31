#include "cub3D.h"

void	raycaster_start(t_all *all)
{
	int x = -1;

	while (++x < WIDTH)
	{
		all->rc->cameraX = 2 * x / (double)WIDTH - 1;
		all->rc->rayDirX = all->player->dirX +
					all->plane->planeX * all->rc->cameraX;
		all->rc->rayDirY = all->player->dirY +
					all->plane->planeY * all->rc->cameraX;
		all->rc->mapX = (int)(all->player->posX);
		all->rc->mapY = (int)(all->player->posY);
		if (all->rc->rayDirX == 0)
			all->rc->deltaDistX = 1e30;
		else
			all->rc->deltaDistX = fabs(1 / all->rc->rayDirX);
		if (all->rc->rayDirY == 0)
			all->rc->deltaDistY = 1e30;
		else
			all->rc->deltaDistY = fabs(1 / all->rc->rayDirY);
		raycaster_second_part(all);
		dda_algorithm(all);
		print_raycasted_map(x, all);
	}
}

void	raycaster_second_part(t_all *all)
{
	t_raycast * rc = all->rc;

	rc->hit = 0;
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (all->player->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - all->player->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (all->player->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - all->player->posY) * rc->deltaDistY;
	}
	all->rc = rc;
}

void	dda_algorithm(t_all *all)
{
	while (all->rc->hit == 0)
	{
		if (all->rc->sideDistX < all->rc->sideDistY)
			{
				all->rc->sideDistX += all->rc->deltaDistX;
				all->rc->mapX += all->rc->stepX;
				all->rc->side = 0;
			}
			else
			{
				all->rc->sideDistY += all->rc->deltaDistY;
				all->rc->mapY += all->rc->stepY;
				all->rc->side = 1;
			}
			if (all->m->map[all->rc->mapY][all->rc->mapX] == '1')
				all->rc->hit = 1;
			dda_algorithm_second_part(all);
	}
}

void	dda_algorithm_second_part(t_all *all)
{
	if (all->rc->side == 0)
		all->rc->perpWallDist = all->rc->sideDistX - all->rc->deltaDistX;
	else
		all->rc->perpWallDist = all->rc->sideDistY - all->rc->deltaDistY;
	all->rc->lineHeight = (int)(HEIGHT / all->rc->perpWallDist);
	all->rc->drawStart = -all->rc->lineHeight / 2 + HEIGHT / 2;
	if (all->rc->drawStart < 0)
		all->rc->drawStart = 0;
	all->rc->drawEnd = all->rc->lineHeight / 2 + HEIGHT / 2;
	if (all->rc->drawEnd >= HEIGHT)
		all->rc->drawEnd = HEIGHT - 1;
}
