/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 06:12:28 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/13 06:19:48 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_close(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	while (i + 1 < info->com_count)
	{
		waitpid(exec->pid_tab[i], NULL, 0);
		if (i != 0)
			close(exec->fd_tab[i]);
		i++;
	}
}

void	init_fd_pid(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	exec->pid_tab = stock_malloc(sizeof(pid_t) * info->com_count, \
		&info->exec_mem);
	if (!exec->pid_tab)
		return (ft_error(ERROR99, info));
	exec->fd_tab = stock_malloc(sizeof(int) * info->com_count, \
		&info->exec_mem);
	if (!exec->fd_tab)
		return (ft_error(ERROR99, info));
	while (i < (info->com_count - 1))
	{
		exec->pid_tab[i] = -1;
		i++;
	}
	return ;
}

void	add_pid(t_info *info, t_exec *exec, pid_t pid)
{
	int	i;

	i = 0;
	while (i + 1 < info->com_count)
	{
		if (exec->pid_tab[i] < 0)
			break ;
		i++;
	}
	exec->pid_tab[i] = pid;
	exec->fd_tab[i] = exec->fd;
}

char	**get_big_path(t_info *info, char **envp)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	splitted = ft_split((envp[i] + 5), ':', &info->exec_mem);
	if (!splitted)
		return (ft_error(ERROR99, info), NULL);
	return (splitted);
}

int	contains_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
