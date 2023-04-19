/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:48:56 by mgagne            #+#    #+#             */
/*   Updated: 2023/04/19 20:09:31 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	heredoc(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	int		fd[2];
	char	*result;

	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	while (42)
	{
		result = readline(BLACK"> "WHITE);
		if (result == NULL)
			return (ft_error(WARNING, info), 1);
		if (ft_strcmp(result, lst_cmd.dir->dest))
			break ;
		write(fd[1], result, ft_strlen(result));
		write(fd[1], "\n", 1);
		free(result);
	}
	free(result);
	exec->in_fd = fd[0];
	close(fd[1]);
	return (0);
}
/*
int	call_heredoc(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	int		fd[2];
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info), 1);
	else if (pid == 0)
	{
		//signal(SIGINT, catch_signals_heredoc);
		//heredoc(info, exec, lst_cmd, fd);
		exit(1);
	}
	printf("exit");
	waitpid(pid, &exit_status, 0);
	set_exitstatus(WEXITSTATUS(exit_status));
	close(fd[1]);
	return (0);
}
*/

int	redirect(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	while (lst_cmd.dir)
	{
		if (ft_strcmp(lst_cmd.dir->type, "<<"))
		{
			if (heredoc(info, exec, lst_cmd))
				return (1);
		}
		else // j'ai rajouté ca il faudra le mettre dans une autre fonction
		{
			if (is_contain_env(lst_cmd.dir->dest) == 1)
				lst_cmd.dir->dest = swap_envstr(lst_cmd.dir->dest, info, info->envp);
			else if (is_contain_env(lst_cmd.dir->dest) == 2)
				lst_cmd.dir->dest = swap_exit(lst_cmd.dir->dest, info);
		}
		if (ft_strcmp(lst_cmd.dir->type, "<"))
			exec->in_fd = open(lst_cmd.dir->dest, O_RDONLY);
		else if (ft_strcmp(lst_cmd.dir->type, ">"))
			exec->out_fd = open(lst_cmd.dir->dest, \
			O_RDWR | O_TRUNC | O_CREAT, 0644);
		else if (ft_strcmp(lst_cmd.dir->type, ">>"))
			exec->out_fd = open(lst_cmd.dir->dest, \
			O_RDWR | O_APPEND | O_CREAT, 0644);
		lst_cmd.dir = lst_cmd.dir->next;
	}
	if (exec->in_fd == -1)
		return (ft_error(ERROR14, info), 1);
	if (exec->out_fd == -1)
		return (ft_error(ERROR15, info), 1);
	return (0);
}
