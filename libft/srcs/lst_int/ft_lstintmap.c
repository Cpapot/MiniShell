/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstintmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:54:56 by cpapot            #+#    #+#             */
/*   Updated: 2022/12/10 18:31:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_int_list	*ft_lstintmap(t_int_list *lst, int (*f)(int))
{
	t_int_list	*start;
	t_int_list	*new;

	if (lst == NULL || f == NULL)
		return (NULL);
	start = ft_lstintnew(f(lst->cont));
	lst = lst->next;
	while (lst)
	{
		new = ft_lstintnew(f(lst->cont));
		if (new == NULL)
		{
			ft_lstintclear(&start);
			return (NULL);
		}
		ft_lstintadd_back(&start, new);
		lst = lst->next;
	}
	return (start);
}
