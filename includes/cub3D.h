#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 300
# define HEIGHT 300

# define X_SIZE 	500
# define Y_SIZE 	500

# define ESC 		65307

# define RED 		0x00FF0000
# define BLUE		0x000000FF
# define WHITE		0xFFFFFFFF
# define BLACK		0x00000000
# define CYAN		0x80A6FF

# define DOWN		65364
# define UP			65362
# define LEFT		65361
# define RIGHT		65363

# define W_UP		119
# define S_DOWN 	115
# define A_LEFT 	97
# define D_RIGHT	100

typedef struct s_time
{
	double time;
	double old_time;
}				t_time;

typedef struct s_plane
{
	double	planeX;
	double	planeY;
}				t_plane;

// typedef struct s_direction
// {

// }				t_direction;

typedef struct s_player
{
	char			*player_on_map;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
}				t_player;

typedef struct	s_ch_map
{
	int 	n;
	int		s;
	int		w;
	int		e;
	int		amount;
	int		space_line;
}				t_ch_map;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_check
{
	int		nt;
	int		st;
	int		wt;
	int		et;
	int		floor;
	int		ceiling;
	int		amount;
	int	 	fd;
	char	*line;
	char	*trimmed;
}				t_check;

typedef struct	s_win
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_win;

typedef struct	s_data
{
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*n_texture;
	int		ceiling[3];
	int		floor[3];
}				t_data;

typedef struct	s_map
{
	char	**map;
	int		width;
	int		height;
}				t_map;

typedef struct	s_all
{
	t_win		*win;
	t_data		*data;
	t_map		*m;
	t_ch_map	*checker;
	t_player	*player;
	t_plane		*plane;
	t_time		*time;
	char		*line;
}				t_all;


// utilis.c //

void	error_exit(char *str, int num);
void	print_double_array(t_map *m);
char	*ft_spaces_str(int width, int len);


// Minilibx_functions.c //

void	my_mlx_pixel_put(t_win *win, int x, int y, int color);
int		key_hook(int key_code, t_all *all);


// executing.c //

void	print_pixel_scale(int x_c, int y_c, int color, t_all *all);
void	print_map(t_all *all);
void	executing(t_all *all);
void	print_raycaster(t_all *all);
void	printVerticalLine(int x, int drawStart, int drawEnd, t_all *all);
// void	init_data_for_execution(t_all *all);

// free_memory.c //

void	free_chained_list(t_list *head);
void	free_memory(t_all *all);
void	free_double_massive(char **map);
void	free_double_array(char **arr);


// parse_data.c //

void	parse_data(char **argv, t_all *all);
void	skip_empty_lines(t_check *ch);
void	parse_map(t_check *ch, t_all *all);
void	check_map_correctness(t_all *all);
void	make_double_array_map(t_all *all, t_list *lst, int height, int width);


// color_floor_and_ceiling_checker.c //

int		ft_atoi_color(const char *str);
char	*add_color_to_struct(char *str, t_color *col, int index);
void	check_correctness_of_color(char *str, t_color *col);
void	add_color_of_floor_and_ceiling(char **args, t_check *ch, t_data *data);


// init_structs.c //

void	init_check_struct(t_check	*ch);
void	init_player_checker_struct(t_all *all);
void	add_player_to_struct(t_all *all, int i, int j, char direction);
void	fill_direction_vector(char direction, t_all *all);


// check_zeros_and_player.c //

void	check_if_map_has_player(t_all *all);
void	check_zeros_at_corners(t_all *all, int i, int j);
int		check_if_symbol_is_zero_or_player(t_all *all, char **map, int i, int j);
int		check_if_symbol_is_zero(t_all *all, char **map, int i, int j);
void	check_one_player(t_all *all, char **map, int i, int j);

// check_texture.c //

void	check_path_to_texture(char *str);
void	add_path_to_texture(char **args, t_check *ch, t_data *data);
void	add_texture_to_struct(t_data *data, t_check *ch);


// check_spaces.c //

void	check_spaces(t_all *all, char **map, int i, int j);
void	check_line_for_spaces(t_all *all, char **map, int i);

# endif