/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_invoke.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:58:49 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/20 07:09:16 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE	1024

static void	exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	close(fd[0]);
	if (exec->in_fd != -2)
	{
		if (dup2(exec->in_fd, STDIN_FILENO) == -1)
			return (ft_error(ERROR13, info));
	}
	else if (dup2(exec->fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (exec->out_fd != -2)
	{
		if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
			return (ft_error(ERROR13, info));
	}
	else if (exec->end == 0 && dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (execve(exec->path, cmd, exec->envp) == -1)
		return (ft_error(ERROR12, info), exit(1));
	exit(0);
}

int	exec_file(t_info *info, t_exec *exec, char **cmd_tab)
{
	char	*pwd;
	char	buffer[BUFFER_SIZE];

	if (cmd_tab[0][0] == '.')
	{
		pwd = getcwd(buffer, BUFFER_SIZE);
		exec->path = ft_strjoin(pwd, &cmd_tab[0][1], &info->exec_mem);
		if (!exec->path)
			return (ft_error(ERROR99, info), 1);
	}
	else if (cmd_tab[0][0] == '/')
		exec->path = cmd_tab[0];
	if (access(exec->path, F_OK) == -1)
		return (ft_error(ERROR2, info), 1);
	return (0);
}

int	handle_command(t_info *info, t_exec *exec, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	signal(SIGINT, catch_signals_child);
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info), 1);
	else if (pid == 0)
		exec_command(info, exec, fd, cmd);
	add_pid(info, exec, pid);
	close(fd[1]);
	exec->fd = fd[0];
	return (0);
}
