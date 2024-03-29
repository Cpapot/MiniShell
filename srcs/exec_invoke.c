/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_invoke.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:58:49 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/05 14:32:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE	1024

static void	exec_bi_or_path(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	if (is_builtins(exec->actual_cmd.command))
	{
		close(exec->fd);
		if (exec->out_fd != -2 || exec->end == 1)
			find_builtins(exec->actual_cmd.command, info, exec->out_fd);
		else
			find_builtins(exec->actual_cmd.command, info, fd[1]);
	}
	else
	{
		exec->path = get_path(info, exec->paths, cmd[0]);
		if (!exec->path)
			return ;
		else
			exec_command(info, exec, fd, cmd);
	}
}

static int	search_and_exec(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	if (!contains_slash(cmd[0]))
	{
		if (access(cmd[0], F_OK | X_OK) != -1)
			exec_command(info, exec, fd, cmd);
		else
			exec_bi_or_path(info, exec, fd, cmd);
	}
	else
	{
		if (exec_file(info, exec, cmd))
			close_minishell(info, get_exitstatus());
		exec_command(info, exec, fd, cmd);
	}
	close_minishell(info, get_exitstatus());
	return (1);
}

void	exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
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
	{
		ft_error(ERROR12, info);
		return (close_minishell(info, 1));
	}
	exit(1);
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
	if (access(exec->path, F_OK | X_OK) == -1)
		return (ft_error(ERROR2, info), 1);
	return (0);
}

int	handle_command(t_info *info, t_exec *exec, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	add_fd(&exec->fd_list, fd[0], info->exec_mem);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info), 1);
	else if (pid == 0)
	{
		signal(SIGINT, &catch_signals_child);
		signal(SIGQUIT, &catch_signals_child);
		close(fd[0]);
		search_and_exec(info, exec, fd, cmd);
		close_minishell(info, 0);
	}
	add_pid(info, exec, pid);
	exec->fd = fd[0];
	close(fd[1]);
	return (0);
}
