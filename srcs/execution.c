/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/14 14:13:23 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define BUFFER_SIZE	1024

void	heredoc(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	int		fd[2];
	char	*result;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info));
	while (42)
	{
		result = readline(BLACK"> "WHITE);
		// printf("result : \"%s\" === dir : \"%s\"\n", result, lst_cmd.dir->dest);
		// printf("%d\n", ft_strncmp(result, lst_cmd.dir->dest, ft_strlen(result)));
		if (ft_strcmp(result, lst_cmd.dir->dest))
			break ;
		write(fd[0], result, ft_strlen(result));
		write(fd[0], "\n", 1);
		free(result);
	}
	free(result);
	exec->in_fd = fd[0];
	close(fd[1]);
	return ;
}

void	redirect(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	while (lst_cmd.dir)
	{
		if (ft_strcmp(lst_cmd.dir->type, "<"))
			exec->in_fd = open(lst_cmd.dir->dest, O_RDONLY);
		else if (ft_strcmp(lst_cmd.dir->type, ">"))
			exec->out_fd = open(lst_cmd.dir->dest, \
			O_RDWR | O_TRUNC | O_CREAT, 0644);
		else if (ft_strcmp(lst_cmd.dir->type, ">>"))
			exec->out_fd = open(lst_cmd.dir->dest, \
			O_RDWR | O_APPEND | O_CREAT, 0644);
		else if (ft_strcmp(lst_cmd.dir->type, "<<"))
			heredoc(info, exec, lst_cmd);
		lst_cmd.dir = lst_cmd.dir->next;
	}
	if (exec->in_fd == -1)
		return (ft_error(ERROR14, info));
	if (exec->out_fd == -1)
		return (ft_error(ERROR15, info));
}

char	**cmd_to_tab(t_info *info, t_commands cmd)
{
	char	**result;
	t_list	*lst;
	int		j;
	int		size;

	lst = cmd.command;
	size = ft_lstsize(lst) + 1;
	result = stock_malloc(sizeof(char *) * size, &info->exec_mem);
	j = 0;
	while (lst && lst->content)
	{
		result[j] = ft_strdup(lst->content, &info->exec_mem);
		lst = lst->next;
		j++;
	}
	result[j] = NULL;
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
	if (exec->in_fd != -2 && dup2(exec->in_fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	else if (dup2(exec->fd, STDIN_FILENO) == -1)
		return (ft_error(ERROR13, info));
	if (exec->end == 0 && dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_error(ERROR13, info));
	else if (exec->out_fd != -2 && dup2(exec->out_fd, STDOUT_FILENO) == -1)
		return (ft_error(ERROR13, info));
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
	signal(SIGINT, catch_signals_child);
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info));
	else if (pid == 0)
		exec_command(info, exec, fd, cmd);
	add_pid(info, exec, pid);
	close(fd[1]);
	exec->fd = fd[0];
}

void	exec_file(t_info *info, t_exec *exec, char **cmd_tab)
{
	char	*pwd;
	char	buffer[BUFFER_SIZE];

	if (cmd_tab[0][0] == '.')
	{
		pwd = getcwd(buffer, BUFFER_SIZE);
		exec->path = ft_strjoin(pwd, &cmd_tab[0][1], &info->exec_mem);
		if (exec->path == NULL)
			ft_error(ERROR99, info);
	}
	else if (cmd_tab[0][0] == '/')
		exec->path = cmd_tab[0];
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
			if (find_builtins(lst_cmd.command, info, exec->out_fd) == 0)
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
		{
			redirect(info, exec, cmds[i]);
			if (exec->in_fd == -1 || exec->out_fd == -1)
				return ;
			search_exec(info, exec, cmds[i]);
			exec->in_fd = -2;
			exec->out_fd = -2;
		}
		i++;
	}
}

void	init_exec(t_info *info, t_exec *exec)
{
	exec->paths = get_big_path(info, info->envp);
	exec->envp = info->envp;
	exec->end = 0;
	exec->fd = STDIN_FILENO;
	exec->in_fd = -2;
	exec->out_fd = -2;
	init_fd_pid(info, exec);
}

/*
This function handles all the execution process of the commands
*/
void	execution(t_info *info)
{
	t_exec	exec;

	init_exec(info, &exec);
	start_exec(info, &exec);
	wait_close(&exec);
	stock_free(&info->exec_mem);
	return ;
}
