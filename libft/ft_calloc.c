/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:07:26 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:07:27 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	void	*temp;

	pointer = malloc((count) * size);
	if (pointer == NULL)
		return (NULL);
	temp = pointer;
	ft_memset(pointer, 0, (size * count));
	return (temp);
}
