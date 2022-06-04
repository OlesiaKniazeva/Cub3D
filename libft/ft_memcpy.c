/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:57 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:58 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp;
	char	*source;

	temp = (char *) dst;
	source = (char *) src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n)
	{
		*temp = *source;
		source++;
		temp++;
		n--;
	}
	return (dst);
}
