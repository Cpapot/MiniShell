/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/12 19:39:48 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_string_cmd(t_info *info, t_commands cmd)
{
	char	**result;
	t_list	*lst;
	int		i;
	int		j;

	result = stock_malloc(sizeof(char *) * info->com_count, &info->exec_mem);
	i = 0;
	while (i + 1 < info->com_count)
	{
		lst = cmd.command;
		j = 0;
		while (lst && lst->content)
		{
			result[j] = ft_strndup(lst->content, \
				ft_strlen(lst->content), &info->exec_mem);
			lst = lst->next;
			j++;
		}
		result[j] = NULL;
		i++;
	}
	return (result);
}

char	*check_path(t_info *info, char *path, t_memlist **mem, char **cmd)
{
	char	*str;

	str = ft_strjoin(path, "/", mem);
	str = ft_strjoin(str, cmd[0], mem);
	if (!str)
		return (stock_free(mem), ft_error(ERROR99, info), NULL);
	if (access(str, F_OK) != -1)
		return (str);
	return (NULL);
}

char	*get_path(t_info *info, char **path, char **cmd)
{
	t_memlist	*mem;
	int			i;
	char		*str;
	char		*res;

	mem = NULL;
	i = 0;
	while (path[i])
	{
		str = check_path(info, path[i], &mem, cmd);
		if (str)
			break ;
		i++;
	}
	res = ft_strdup(str, &info->exec_mem);
	if (!res)
		return (stock_free(&mem), ft_error(ERROR99, info), NULL);
	return (stock_free(&mem), res);
}

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

void	exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	char	*path;

	close(fd[0]);
	if (dup2(exec->fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (exec->end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (ft_error(ERROR13, info));
	}
	path = get_path(info, exec->path, cmd);
	if (execve(path, cmd, exec->envp) == -1)
	{
		set_exitstatus(errno);
		return (ft_error(ERROR12, info));
	}
	exit(0);
}

void	handle_command(t_info *info, t_exec *exec, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info));
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info));
	else if (pid == 0)
		exec_command(info, exec, fd, cmd);
	add_pid(info, exec, pid);
	close(fd[1]);
	exec->fd = fd[0];
}

void	handle_pipe(t_info *info, t_exec *exec)
{
	int			i;
	t_commands	*cmds;
	char		**cmd;

	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		return (ft_error(ERROR13, info));
	exec->fd = STDIN_FILENO;
	i = 0;
	cmds = info->final_parse;
	while (i + 1 < info->com_count)
	{
		if (i + 2 >= info->com_count)
			exec->end = 1;
		cmd = get_string_cmd(info, cmds[i]);
		if (find_builtins(cmds[i].command, info, 1) == 0)
			handle_command(info, exec, cmd);
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

void	init_exec(t_info *info, t_exec *exec)
{
	exec->path = get_big_path(info, info->envp);
	exec->fd = STDIN_FILENO;
	exec->envp = info->envp;
	exec->end = 0;
	exec->fd = 0;
	exec->in_fd = STDIN_FILENO;
	exec->out_fd = STDOUT_FILENO;
	init_fd_pid(info, exec);
}

/*
This function handles all the execution process of the commands
*/
void	execution(t_info *info)
{
	t_exec	exec;

	init_exec(info, &exec);
	handle_pipe(info, &exec);
	wait_close(info, &exec);
	stock_free(&info->exec_mem);
	return ;
}
