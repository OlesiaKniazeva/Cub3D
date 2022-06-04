/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:10:48 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:10:49 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	neesize;
	int	a;

	a = 0;
	neesize = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (len > 0)
	{
		while (len > 0 && *haystack == needle[a] && *haystack)
		{
			haystack++;
			a++;
			len--;
		}
		if (needle[a] == '\0')
			return ((char *)(haystack - neesize));
		a = 0;
		if (len > 1)
			len--;
		haystack++;
	}
	return (NULL);
}
