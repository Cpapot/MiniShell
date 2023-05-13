/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/13 14:06:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_fd(t_int_list **fd_list, int fd, t_memlist *mem)
{
	t_int_list	*tmp;

	tmp = ft_lstintnew(fd, &mem);
	ft_lstintadd_back(fd_list, tmp);
}

void	close_lst(t_int_list *fd)
{
	while (fd)
	{
		if (fd->cont > 0)
			close(fd->cont);
		fd = fd->next;
	}
}
