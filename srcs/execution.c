/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/13 15:43:08 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE	1024

char	**cmd_to_tab(t_info *info, t_commands cmd)
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
			result[j] = ft_strdup(lst->content, &info->exec_mem);
			lst = lst->next;
			j++;
		}
		result[j] = NULL;
		i++;
	}
	return (result);
}

char	*check_path(t_info *info, char *path, t_memlist **mem, char *cmd)
{
	char	*str;

	str = ft_strjoin(path, "/", mem);
	str = ft_strjoin(str, cmd, mem);
	if (!str)
		return (stock_free(mem), ft_error(ERROR99, info), NULL);
	if (access(str, F_OK) != -1)
		return (str);
	return (NULL);
}

char	*get_path(t_info *info, char **path, char *cmd)
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
	if (!str)
		return (stock_free(&mem), NULL);
	res = ft_strdup(str, &info->exec_mem);
	if (!res)
		return (stock_free(&mem), ft_error(ERROR99, info), NULL);
	return (stock_free(&mem), res);
}

void	exec_command(t_info *info, t_exec *exec, int fd[2], char **cmd)
{
	close(fd[0]);
	if (dup2(exec->fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (exec->end == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (ft_error(ERROR13, info));
	}
	if (execve(exec->path, cmd, exec->envp) == -1)
		return (ft_error(ERROR12, info), exit(1));
	exit(0);
}

void	handle_command(t_info *info, t_exec *exec, char **cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info));
	pid = fork();
	add_pid(info, exec, pid);
	if (pid == -1)
		return (ft_error(ERROR10, info));
	else if (pid == 0)
		exec_command(info, exec, fd, cmd);
	close(fd[1]);
	exec->fd = fd[0];
}

void	exec_file(t_info *info, t_exec *exec, char **cmd_tab)
{
	char	*pwd;
	char	buffer[BUFFER_SIZE];

	pwd = getcwd(buffer, BUFFER_SIZE);
	exec->path = ft_strjoin(pwd, &cmd_tab[0][1], &info->exec_mem);
	if (exec->path == NULL)
		ft_error(ERROR99, info);
}

void	search_exec(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	char	**cmd_tab;

	cmd_tab = cmd_to_tab(info, lst_cmd);
	if (!contains_slash(cmd_tab[0]))
	{
		if (access(cmd_tab[0], F_OK) != -1)
			handle_command(info, exec, cmd_tab);
		else
		{
			if (find_builtins(lst_cmd.command, info, 1) == 0)
			{
				exec->path = get_path(info, exec->paths, cmd_tab[0]);
				if (!exec->path)
					return (ft_error(ERROR2, info));
				else
					handle_command(info, exec, cmd_tab);
			}
		}
	}
	else
	{
		exec_file(info, exec, cmd_tab);
		handle_command(info, exec, cmd_tab);
	}
}


void	start_exec(t_info *info, t_exec *exec)
{
	int			i;
	t_commands	*cmds;

	i = 0;
	cmds = info->final_parse;
	while (i + 1 < info->com_count)
	{
		if (i + 2 >= info->com_count)
			exec->end = 1;
		if (cmds[i].command != NULL && cmds[i].command->content != NULL)
			search_exec(info, exec, cmds[i]);
		i++;
	}
}

void	init_exec(t_info *info, t_exec *exec)
{
	exec->paths = get_big_path(info, info->envp);
	exec->envp = info->envp;
	exec->end = 0;
	exec->fd = STDIN_FILENO;
	exec->in_fd = STDIN_FILENO;
	exec->out_fd = STDOUT_FILENO;
	init_fd_pid(info, exec);
	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		return (ft_error(ERROR13, info));
}

/*
This function handles all the execution process of the commands
*/
void	execution(t_info *info)
{
	t_exec	exec;

	init_exec(info, &exec);
	start_exec(info, &exec);
	wait_close(info, &exec);
	stock_free(&info->exec_mem);
	return ;
}
