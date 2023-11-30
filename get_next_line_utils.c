#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
	{
		return (NULL);
	}
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void free_list(t_list *list)
{
    while (list)
    {
        t_list *temp = list;
        list = list->next;
        free(temp);
    }
}
