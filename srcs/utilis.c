/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:13:39 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:57:59 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	error_exit(char *str, int num)
{
	printf("Error:\n     %s", str);
	exit(num);
}

void	print_double_array(t_map *m)
{
	char	**map;

	map = m->map;
	while (*map)
	{
		printf("%s\n", *map);
		map++;
	}
}

char	*ft_spaces_str(int width, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (width - len + 1));
	while (i < width - len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}
