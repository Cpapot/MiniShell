/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:48:56 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/06 17:06:52 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	heredoc(t_info *info, t_commands lst_cmd, int fd[2])
{
	char	*result;
	char	*tmp;

	while (42)
	{
		ft_printf_fd(2, GREEN"> "WHITE);
		result = get_next_line(0);
		if (result == NULL)
			return (ft_error(WARNING, info), close(fd[1]), 1);
		tmp = ft_substr(result, 0, ft_strlen(result) - 1);
		if (ft_strcmp(tmp, lst_cmd.dir->dest))
			break ;
		ft_printf_fd(fd[1], result);
		free(tmp);
		free(result);
	}
	free(tmp);
	free(result);
	close(fd[1]);
	return (0);
}

int	call_heredoc(t_info *info, t_commands lst_cmd)
{
	int		fd[2];
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == -1)
		return (ft_error(ERROR11, info), 1);
	pid = fork();
	if (pid == -1)
		return (ft_error(ERROR10, info), 1);
	else if (pid == 0)
	{
		signal(SIGINT, catch_signals_heredoc);
		heredoc(info, lst_cmd, fd);
		exit(1);
	}
	waitpid(pid, &exit_status, 2);
	set_exitstatus(exit_status);
	return (fd[0]);
}

static int	env_check(t_info *info, t_commands *lst_cmd)
{
	if (is_contain_env((*lst_cmd).dir->dest) == 1)
		(*lst_cmd).dir->dest = \
			swap_envstr((*lst_cmd).dir->dest, info, info->envp);
	else if (is_contain_env((*lst_cmd).dir->dest) == 2)
		(*lst_cmd).dir->dest = swap_exit((*lst_cmd).dir->dest, info);
	return (0);
}

int	redirect(t_info *info, t_exec *exec, t_commands lst_cmd)
{
	while (lst_cmd.dir)
	{
		if (ft_strcmp(lst_cmd.dir->type, "<<"))
			exec->in_fd = call_heredoc(info, lst_cmd);
		else if (env_check(info, &lst_cmd))
			return (1);
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
