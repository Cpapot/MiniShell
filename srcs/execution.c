/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/09 19:51:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	search_exec2(t_info *info, t_exec *exec, t_commands lst, char **cmd)
{
	int		fd[2];

	if (is_builtins(lst.command))\
	{
		if (exec->end == 1 || exec->out_fd != -2)
			find_builtins(lst.command, info, exec, exec->out_fd);
		else
		{
			if (pipe(fd) == -1)
				return (ft_error(ERROR11, info), 1);
			find_builtins(lst.command, info, exec, fd[1]);
			close(fd[1]);
			exec->fd = fd[0];
		}
	}
	else
	{
		exec->path = get_path(info, exec->paths, cmd[0]);
		if (!exec->path)
			return (1);
		else
		{
			if (handle_command(info, exec, cmd))
				return (1);
		}
	}
	return (0);
}

static int	search_exec(t_info *info, t_exec *exec, t_commands lst, char **cmd)
{
	if (!contains_slash(cmd[0]))
	{
		if (!ft_strcmp(cmd[0], "pwd") && access(cmd[0], F_OK) != -1)
		{
			if (handle_command(info, exec, cmd))
				return (1);
		}
		else
		{
			if (search_exec2(info, exec, lst, cmd))
				return (1);
		}
	}
	else
	{
		if (exec_file(info, exec, cmd))
			return (1);
		if (handle_command(info, exec, cmd))
			return (1);
	}
	return (0);
}

/*
This function loops on every command, if there are redirections they are handled,
after that we get the command from a chained list to an array of strings,
which we can send as a parameter to the search_exec function.
*/
static int	start_exec(t_info *info, t_exec *exec)
{
	int			i;
	t_commands	*cmds;
	char		**cmd_tab;

	i = 0;
	cmds = info->final_parse;
	while (i + 1 < info->com_count)
	{
		if (i + 2 >= info->com_count)
			exec->end = 1;
		if (redirect(info, exec, cmds[i]))
			return (1);
		if (cmds[i].command != NULL && cmds[i].command->content != NULL)
		{
			cmd_tab = cmd_to_tab(info, cmds[i]);
			if (!cmd_tab)
				return (1);
			if (search_exec(info, exec, cmds[i], cmd_tab))
				return (1);
			exec->in_fd = -2;
			exec->out_fd = -2;
		}
		i++;
	}
	return (0);
}

/*
This function initialize all the values of our t_exec structure
*/
static int	init_exec(t_info *info, t_exec *exec)
{
	exec->paths = get_big_path(info, info->envp);
	exec->envp = info->envp;
	exec->end = 0;
	exec->fd = STDIN_FILENO;
	exec->in_fd = -2;
	exec->out_fd = -2;
	if (init_fd_pid(info, exec))
		return (1);
	return (0);
}

/*
This function handles all the execution major steps
*/
void	execution(t_info *info)
{
	t_exec	exec;

	if (init_exec(info, &exec))
		return ;
	if (start_exec(info, &exec))
		return ;
	wait_close(&exec);
	stock_free(&info->exec_mem);
	return ;
}
