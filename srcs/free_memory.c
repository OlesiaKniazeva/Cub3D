#include "cub3D.h"

void	free_chained_list(t_list *head)
{
	t_list	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_double_array(char **arr)
{
	char **pointer;

	pointer = arr;
	while (*arr)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
	free(pointer);
	arr = NULL;
}

void	free_double_massive(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		++i;
	}
	free(map);
}

void	free_memory(t_all *all)
{
	// free(all->win);
	free(all->checker);
	free(all->data->e_texture);
	free(all->data->s_texture);
	free(all->data->n_texture);
	free(all->data->w_texture);
	free(all->data);
	free_double_massive(all->m->map);
	free(all->m);
	free(all->player);
}
