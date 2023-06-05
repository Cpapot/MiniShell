/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:53:56 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/05 14:02:43 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_close(t_exec *exec)
{
	int	signal;
	int	i;
	int	exit_status;

	signal = 0;
	i = 0;
	exit_status = 0;
	while (exec->pid_tab[i] >= 0)
	{
		waitpid(exec->pid_tab[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			set_exitstatus(WEXITSTATUS(exit_status));
		else if (WIFSIGNALED(exit_status) && signal == 0)
		{
			signal = 1;
			catch_signals_child(WTERMSIG(exit_status));
		}
		if (i != 0)
			close(exec->fd_tab[i]);
		i++;
	}
	if (exec->final_execstat != -1)
		set_exitstatus(exec->final_execstat);
	close_lst(exec->fd_list);
}

int	init_fd_pid(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	exec->pid_tab = stock_malloc(sizeof(pid_t) * info->com_count + 1, \
		&info->exec_mem);
	if (!exec->pid_tab)
		return (ft_error(ERROR99, info), 1);
	exec->fd_tab = stock_malloc(sizeof(int) * info->com_count, \
		&info->exec_mem);
	if (!exec->fd_tab)
		return (ft_error(ERROR99, info), 1);
	while (i + 1 < info->com_count)
	{
		exec->pid_tab[i] = -1;
		i++;
	}
	exec->pid_tab[i] = -1;
	return (0);
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
