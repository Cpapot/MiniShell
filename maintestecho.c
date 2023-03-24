#include <stdlib.h>
#include <stdio.h>
#include "libft/includes/libft.h"

void	echo(t_list *lst, int out_fd);

int main(int argc, char **argv)
{
	t_memlist *stock;
    t_list *lst;
    int out_fd = 1; // sortir les données dans la console
    int i;

	stock = NULL;
    lst = NULL;
    i = 1;
    while (i < argc)
    {
        ft_lstadd_back(&lst, ft_lstnew(argv[i], &stock));
        i++;
    }
    echo(lst, out_fd);
    ft_lstclear(&lst);
    return (0);
}
