/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:37 by myael             #+#    #+#             */
/*   Updated: 2022/06/04 13:08:38 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	amount;

	amount = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		amount++;
	}
	return (amount);
}
