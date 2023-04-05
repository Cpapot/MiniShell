/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/05 04:28:02 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_path(char **path, t_commands cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i], "/", NULL);
		str = ft_strjoin(str, cmd[0], NULL);
		if (access(str, F_OK) != -1)
			break ;
		i++;
		free(str);
	}
	if (!str)
		return (NULL);
		// ft_print_error("no path exists where this command is executable");
	return (str);
}

void	set_finish(t_info *info, int n)
{
	info->is_finish = n;
	return ;
}

void	wait_close(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	while (i + 1 < info->com_count)
	{
		waitpid(exec->pid_tab[i], NULL, 0);
		close(exec->fd_tab[i]);
		i++;
	}
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

void	exec_command(t_exec *exec, int fd[2], t_commands cmd, int end)
{
	char	*path;

	close(fd[0]);
	if (dup2(exec->fd, STDIN_FILENO) == -1)
		return ;
		// free_all(arg, "dup2 failed");
	if (end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return ;
			// free_all(arg, "dup2 failed");
	}
	path = get_path(exec->path, cmd);
	if (execve(path, cmd, exec->envp) == -1)
		// free_all(arg, "execution failed");
		return ;
}

void	handle_command(t_info *info, t_exec *exec, t_commands cmd, int end)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (wait_close(info, exec), set_finish(info, 1));
	pid = fork();
	if (pid == -1)
		return (wait_close(info, exec), set_finish(info, 1));
	else if (pid == 0)
		exec_command(exec, fd, cmd, end);
	add_pid(info, exec, pid);
	close(fd[1]);
	exec->fd = fd[0];
}

void	handle_pipe(t_info *info, t_exec *exec)
{
	int			i;
	t_commands	*cmds;

	// if (dup2(arg->in_fd, STDIN_FILENO) == -1)
	// 	free_all(arg, "dup2 error");
	// if (dup2(arg->out_fd, STDOUT_FILENO) == -1)
	// 	free_all(arg, "dup2 error");
	info->is_finish = info->is_finish;
	i = 0;
	cmds = info->final_parse;
	while (i + 2 < info->com_count)
	{
		handle_command(info, exec, cmds[i], 0);
		i++;
	}
	handle_command(info, exec, cmds[i], 1);
}

void	init_fd_pid(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	exec->pid_tab = stock_malloc(sizeof(pid_t) * info->com_count, \
		&info->exec_mem);
	if (!exec->pid_tab)
		return (set_finish(info, 1));
	exec->fd_tab = stock_malloc(sizeof(int) * info->com_count, \
		&info->exec_mem);
	if (!exec->fd_tab)
		return (set_finish(info, 1));
	while (i < (info->com_count - 1))
	{
		exec->pid_tab[i] = -1;
		i++;
	}
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
		return (set_finish(info, 1), NULL);
	return (splitted);
}

void	init_exec(t_info *info, t_exec *exec)
{
	exec->path = get_big_path(info, info->envp);
	if (info->is_finish != 0)
		return ;
	exec->fd = STDIN_FILENO;
	exec->envp = info->envp;
	init_fd_pid(info, exec);
}

/*
This function handles all the execution process of the commands
*/
void	execution(t_info *info)
{
	t_exec	exec;

	init_exec(info, &exec);
	if (info->is_finish != 0)
		return ;
	handle_pipe(info, &exec);
}

// info->exec_mem;
// info->envp;
// info->command;
// info->com_count;
