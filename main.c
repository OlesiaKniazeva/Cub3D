#include "minilibx_linux/mlx.h"
# define TEX_W 30
# define TEX_H 30
#include <stdio.h>
#include <stdlib.h>

typedef struct s_win {
    void	*mlx;
	void	*img;
    void	*win;
	char	*path;
	int		img_width;
	int		img_height;
    int		bpp;
	int		l_len;
	int		end;
    char *addr;
}t_win;

unsigned int	color_pixel_texture(t_win* win, int y, int x)
{
	char			*adr;
	unsigned int	color;

	adr = win->addr + (x * win->l_len + y * (win->bpp / 8));
	color = *(unsigned int *)adr;
	return (color);
}

int	main(void)
{
    t_win win;

	win.mlx = mlx_init();
    win.win = mlx_new_window(win.mlx, 600, 600, "Cub3D");
    win.path = "texture/e_wall.xmp";
	win.img = mlx_xpm_file_to_image(win.mlx, win.path, &win.img_width, &win.img_height);
    if (!win.img) {
        printf("Error\n");
    }
    win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.l_len, &win.end);


    unsigned int **texture = malloc(sizeof(int *) * win.img_width);
	for (int x = 0; x < TEX_W; ++x) {
        *texture = malloc(sizeof(int) * win.img_height);
		for(int y = 0; y < TEX_H; ++y) {
            texture[y][x] = color_pixel_texture(&win, y, x);
			// texture[TEX_W * y + x] = 65536 * 192 * (x % 16 && y % 16);
		}
	}
    mlx_put_image_to_window(win.mlx, win.win, win.img, 0, 0);
    mlx_loop(win.mlx);

}

