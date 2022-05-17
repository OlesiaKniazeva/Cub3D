#include "cub3D.h"

void	init_check_struct(t_check	*ch)
{
	ch->amount = 0;
	ch->nt = 0;
	ch->st = 0;
	ch->wt = 0;
	ch->et = 0;
	ch->floor = 0;
	ch->ceiling = 0;
	ch->line = NULL;
	ch->trimmed = NULL;
	ch->fd = -1;
}

void	init_player_checker_struct(t_all *all)
{
	t_ch_map *check;

	check = malloc(sizeof(t_ch_map));
	check->amount = 0;
	check->e = 0;
	check->n = 0;
	check->s = 0;
	check->w = 0;
	check->space_line = 0;
	all->checker = check;
}

void	fill_direction_vector(char direction, t_all *all)
{
	if (direction == 'W')
	{
		all->player->dirX = -1;
		all->player->dirY = 0;
		all->plane->planeX = 0;
		all->plane->planeY = 0.66;
	}
	else if (direction == 'E')
	{
		all->player->dirX = 1;
		all->player->dirY = 0;
		all->plane->planeX = 0;
		all->plane->planeY = -0.66;
	}
	else if (direction == 'S')
	{
		all->player->dirX = 0;
		all->player->dirY = 1;
		all->plane->planeX = 0.66;
		all->plane->planeY = 0;
	}
	else if (direction == 'N')
	{
		all->player->dirX = 0;
		all->player->dirY = -1;
		all->plane->planeX = -0.66;
		all->plane->planeY = 0;
	}
}

void	add_player_to_struct(t_all *all, int i, int j, char direction)
{
	t_player	*player;
	t_plane		*plane;

	player = malloc(sizeof(t_player));
	plane = malloc(sizeof(t_plane));
	all->plane = plane;
	player->posX = j + 0.5;
	player->posY = i + 0.5;
	all->m->map[i][j] = '0';
	player->player_on_map = &all->m->map[i][j];
	all->player = player;
	fill_direction_vector(direction, all);
}
