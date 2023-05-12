/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/12 19:24:42 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*inttovoid(int nb, t_memlist *mem)
{
	void	*ptr;

	ptr = stock_malloc(sizeof(int), &mem);
	*((int*)ptr) = nb;
	return (ptr);
}

void	add_fd(t_list **fd_list, int fd, t_memlist *mem)
{
	t_list	*tmp;

	tmp = ft_lstnew(inttovoid(fd, mem), &mem);
	ft_lstadd_back(fd_list, tmp);
}

void	close_lst(t_list *fd)
{
	while (fd)
	{
		if (*((int*)fd->content) > 0)
			close(*((int*)fd->content));
		fd = fd->next;
	}
}
