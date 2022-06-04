/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:05 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:06 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_amount(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		count++;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		amount;

	amount = ft_amount(n);
	string = malloc(sizeof(char) * (amount + 1));
	if (string == NULL)
		return (NULL);
	*(string + amount) = '\0';
	if (n == 0)
		*string = '0';
	if (n < 0)
		*string = '-';
	amount--;
	while (amount)
	{
		if (n < 0)
			*(string + amount) = -(n % 10) + '0';
		else
			*(string + amount) = (n % 10) + '0';
		n /= 10;
		amount--;
	}
	if (n > 0)
		*string = n + '0';
	return (string);
}
