/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:10:54 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:10:55 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*new;
	int		a;

	a = ft_strlen(s);
	while (a >= 0)
	{
		if (*(s + a) == c)
		{
			new = (char *)(s + a);
			return (new);
		}
		a--;
	}
	new = 0;
	return (new);
}
