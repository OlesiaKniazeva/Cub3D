/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:47 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:48 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*string;
	void		*new;
	char		d;

	d = c;
	string = (char *)s;
	while (n)
	{
		if (*string == d)
		{
			new = (void *)string;
			return (new);
		}
		string++;
		n--;
	}
	return (NULL);
}
