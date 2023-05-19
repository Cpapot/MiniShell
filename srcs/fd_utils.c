/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:24 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/19 15:50:18 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	empty_pipe(t_exec *exec, t_info *info)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	add_fd(&exec->fd_list, fd[0], info->exec_mem);
	close(fd[1]);
	exec->fd = fd[0];
	return (0);
}

void	r_fd(t_exec	*exec)
{
	exec->in_fd = -2;
	exec->out_fd = -2;
}

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
