/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:48:56 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/19 16:32:28 by cpapot           ###   ########.fr       */
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
			return (ft_error(WARN, info), 0);
		tmp = ft_substr(result, 0, ft_strlen(result) - 1);
		if (tmp == NULL)
			ft_error(ERROR99, info);
		if (ft_strcmp(tmp, lst_cmd.dir->dest))
			break ;
		ft_printf_fd(fd[1], result);
		free(tmp);
		free(result);
	}
	free(tmp);
	free(result);
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
		close(fd[0]);
		signal(SIGINT, catch_signals_heredoc);
		heredoc(info, lst_cmd, fd);
		close(fd[1]);
		close_minishell(info, 0);
	}
	waitpid(pid, &exit_status, 2);
	close(fd[1]);
	set_exitstatus(WEXITSTATUS(exit_status));
	return (fd[0]);
}

static int	env_check(t_info *info, t_commands *lst_cmd)
{
	int		i;
	char	*str;

	str = (*lst_cmd).dir->dest;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			i += quote_size(&str[i], 0);
		else if (str[i] == '$')
		{
			if (is_contain_env(&str[i]) == 1)
				str = swap_envstr(str, info, info->envp, &i);
			else if (is_contain_env(&str[i]) == 2)
				str = swap_exit(str, info, &i);
		}
		i++;
	}
	return (0);
}

int	check_redirect_fd(t_info *info, t_exec *exec)
{
	add_fd(&exec->fd_list, exec->out_fd, info->exec_mem);
	add_fd(&exec->fd_list, exec->in_fd, info->exec_mem);
	if (exec->in_fd == -1)
	{
		return (r_fd(exec), ft_error(ERROR20, info),
			set_final_exitstatus(1, exec), 1);
	}
	if (exec->out_fd == -1)
	{
		return (r_fd(exec), ft_error(ERROR15, info),
			set_final_exitstatus(1, exec), 1);
	}
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
		if (check_redirect_fd(info, exec))
			return (1);
		lst_cmd.dir = lst_cmd.dir->next;
	}
	return (0);
}
