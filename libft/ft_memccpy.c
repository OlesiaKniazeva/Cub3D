/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:42 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:43 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	symbol;

	symbol = c;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n)
	{
		if (*source == symbol)
		{
			*dest = *source;
			dest++;
			return (dest);
		}
		*dest = *source;
		source++;
		dest++;
		n--;
	}
	return (NULL);
}
