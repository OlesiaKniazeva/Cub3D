#include "cub3D.h"

void	make_double_array_map(t_all *all, t_list *lst, int height, int width)
{
	t_list	*head;
	t_map	*m;
	int 	i;
	char	*temp;

	i = -1;
	m = malloc(sizeof(t_map));
	m->map = malloc(sizeof(char *) * (height + 1));
	head = lst;
	while (lst)
	{
		if ((int)ft_strlen(lst->content) < width)
		{
			temp = ft_spaces_str(width, ft_strlen(lst->content));
			m->map[++i] = ft_strjoin(lst->content, temp);
			free(temp);
		}
		else
			m->map[++i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	m->map[++i] = NULL;
	m->height = height;
	m->width = width;
	all->m = m;
	free_chained_list(head);
}

void	check_map_correctness(t_all *all)
{
	char		**map;
	int			i;
	int			j;

	i = -1;
	print_double_array(all->m);
	map = all->m->map;
	while (map[i] && (++i < all->m->height))
	{
		j = -1;
		check_line_for_spaces(all, map, i);
		while (map[i][++j] && j < all->m->width)
		{
			if (map[i][j] == ' ')
				check_spaces(all, map, i, j);
			else if (map[i][j] == '0')
				check_zeros_at_corners(all, i, j);
			else if (map[i][j] == '1')
				;
			else if (map[i][j] == 'N' || map[i][j] == 'S' ||
					 map[i][j] == 'W' || map[i][j] == 'E')
				check_one_player(all, map, i, j);
			else
				error_exit("Invalid symbol in map", 15);
		}
	}
}

void	parse_map(t_check *ch, t_all *all)
{
	t_list	*lst;
	int		height;
	int		width;
	int		temp;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(ch->line));
	width = ft_strlen(ch->line);
	height = 1;
	while (get_next_line(ch->fd, &ch->line))
	{
		ft_lstadd_back(&lst, ft_lstnew(ch->line));
		temp = ft_strlen(ch->line);
		if (temp > width)
			width = temp;
		height++;
	}
	if (height != 1)
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\n");
		if (*(ch->trimmed))
		{
			ft_lstadd_back(&lst, ft_lstnew(ch->line));
			height++;
		}
		free(ch->trimmed);
	}
	make_double_array_map(all, lst, height, width);
	init_player_checker_struct(all);
	check_map_correctness(all);
	check_if_map_has_player(all);
}

void	skip_empty_lines(t_check *ch)
{
	ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
	if (ch->trimmed && *(ch->trimmed))
	{
		free(ch->trimmed);
		return ;
	}
	if (ch->line)
		free(ch->line);
	if (ch->trimmed)
		free(ch->trimmed);
	while (get_next_line(ch->fd, &ch->line))
	{
		ch->trimmed = ft_strtrim(ch->line, " \t\v\f\r");
		if (ch->trimmed && *(ch->trimmed))
		{
			free(ch->trimmed);
			break ;
		}
		free(ch->line);
		ch->line = NULL;
		free(ch->trimmed);
		ch->trimmed = NULL;
	}
	if (!ch->line || !*(ch->line))
		error_exit("Error with map data!", 13);
}


void parse_data(char **argv, t_all *all)
{
	t_data	*data;
	t_check	ch;

	init_check_struct(&ch);
	data = malloc(sizeof(t_data));
	if (!data)
		error_exit("Malloc error", 12);
	ch.fd = open(argv[1], O_RDONLY);
	if (ch.fd == -1)
		error_exit("Couldn't open the file", 2);
	while (get_next_line(ch.fd, &ch.line) && ch.amount < 6)
	{
		ch.trimmed = ft_strtrim(ch.line, " \t\v\f\r");
		free(ch.line);
		if (ch.trimmed && *(ch.trimmed))
			add_texture_to_struct(data, &ch);
		else if (ch.trimmed)
			free(ch.trimmed);
	}
	if (ch.amount < 6)
		error_exit("Not enough data", 10);
	skip_empty_lines(&ch);
	parse_map(&ch, all);
	all->data = data;
	print_double_array(all->m);
	printf("-------\n");
	close(ch.fd);
}