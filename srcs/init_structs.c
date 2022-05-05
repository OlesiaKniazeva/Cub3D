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

void	fill_direction_vector(t_direction *dir, char direction)
{
	if (direction == 'W' || direction == 'E')
	{
		dir->dirY = 0;
		if (direction == 'W')
			dir->dirX = -1;
		else
			dir->dirX = 1;
	}
	else if (direction == 'S' || direction == 'N')
	{
		dir->dirX = 0;
		if (direction == 'S')
			dir->dirY = -1;
		else
			dir->dirY = 1;
	}
}

void	add_player_to_struct(t_all *all, int i, int j, char direction)
{
	t_player	*player;
	t_direction	*dir;

	player = malloc(sizeof(t_player));
	dir = malloc(sizeof(t_direction));
	player->x = j;
	player->y = i;
	fill_direction_vector(dir, direction);
	player->dir = dir;
	all->m->map[i][j] = 'P';
	player->player_on_map = &all->m->map[i][j];
	all->player = player;
}
