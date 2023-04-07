/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/07 04:42:12 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_string_cmd(t_info *info, t_commands cmd)
{
	char	**result;
	t_list	*lst;
	// t_dir	*dir;
	int		i;

	result = stock_malloc(sizeof(char *) * info->com_count, &info->exec_mem);
	i = 0;
	while (i + 1 < info->com_count)
	{
		lst = cmd.command;
		while (lst && lst->content)
		{
			result[i] = ft_strndup(lst->content, \
				ft_strlen(lst->content), &info->exec_mem);
			lst = lst->next;
		}
		i++;
	}
	return (result);
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
		str = ft_strjoin(path[i], "/", &mem);
		if (!str)
			return (stock_free(&mem), NULL);	// malloc error
		str = ft_strjoin(str, cmd[0], &mem);
		if (!str)
			return (stock_free(&mem), NULL);	// malloc error
		if (access(str, F_OK) != -1)
			break ;
		i++;
	}
	if (!str)
		return (stock_free(&mem), NULL);	// error "no path exists where this command is executable"
	res = ft_strdup(str, &info->exec_mem);
	if (!res)
		return (stock_free(&mem), NULL);	// malloc error
	return (stock_free(&mem), res);
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

void	exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	char	*path;

	close(fd[0]);
	if (dup2(exec->fd, STDIN_FILENO) == -1)
		return ;	// error : dup2 function failed to execute
	if (exec->end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return ;	// error : dup2 function failed to execute
	}
	path = get_path(info, exec->path, cmd);
	if (execve(path, cmd, exec->envp) == -1)
		return ;	// error : execve function failed to execute
}

void	handle_command(t_info *info, t_exec *exec, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;	//error
	pid = fork();
	if (pid == -1)
		return ;	//error
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

	// if (dup2(arg->in_fd, STDIN_FILENO) == -1)
	// 	free_all(arg, "dup2 error");
	// if (dup2(arg->out_fd, STDOUT_FILENO) == -1)
	// 	free_all(arg, "dup2 error");
	i = 0;
	cmds = info->final_parse;
	while (i + 2 < info->com_count)
	{
		cmd = get_string_cmd(info, cmds[i]);
		handle_command(info, exec, cmd);
		i++;
	}
	exec->end = 1;
	cmd = get_string_cmd(info, cmds[i]);
	handle_command(info, exec, cmd);
}

void	init_fd_pid(t_info *info, t_exec *exec)
{
	int	i;

	i = 0;
	exec->pid_tab = stock_malloc(sizeof(pid_t) * info->com_count, \
		&info->exec_mem);
	if (!exec->pid_tab)
		return ;	//error
	exec->fd_tab = stock_malloc(sizeof(int) * info->com_count, \
		&info->exec_mem);
	if (!exec->fd_tab)
		return ;	//error
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
		return (NULL);		//error
	return (splitted);
}

void	init_exec(t_info *info, t_exec *exec)
{
	exec->path = get_big_path(info, info->envp);
	if (info->is_finish != 0)
		return ;	//error
	exec->fd = STDIN_FILENO;
	exec->envp = info->envp;
	exec->end = 0;
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
		return ;	//error
	handle_pipe(info, &exec);
	wait_close(info, &exec);
	stock_free(&info->exec_mem);
	return ;
}

// info->exec_mem;
// info->envp;
// info->command;
// info->com_count;
