/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:52 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:53 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*first;
	unsigned const char	*second;

	first = s1;
	second = s2;
	if (n == 0)
		return (0);
	while (n && (*first == *second))
	{
		first++;
		second++;
		n--;
	}
	if (n > 0)
		return (*first - *second);
	else
		return (*(first - 1) - *(second - 1));
}
