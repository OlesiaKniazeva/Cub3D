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
