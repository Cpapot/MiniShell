/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/05 14:57:27 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	search_exec(t_info *info, t_exec *exec, t_commands lst, char **cmd)
{
	if (!cmd)
		return (1);
	exec->actual_cmd = lst;
	if (info->com_count == 2 && is_builtins(lst.command))
	{
		find_builtins(lst.command, info, exec->out_fd);
		return (0);
	}
	else
		if (handle_command(info, exec, cmd))
			return (1);
	return (0);
}

/*
This function loops on every command, if there are redirections they are handled,
after that we get the command from a chained list to an array of strings,
which we can send as a parameter to the search_exec function.
*/
static int	start_exec(t_info *info, t_exec *exec, int tmp)
{
	int			i;
	t_commands	*cmds;
	char		**cmd_tab;

	i = -1;
	cmds = info->final_parse;
	while (++i + 1 < info->com_count)
	{
		exec->final_execstat = -1;
		if (i + 2 >= info->com_count)
			exec->end = 1;
		tmp = redirect(info, exec, cmds[i]);
		if (tmp == -1)
			return (1);
		if (cmds[i].command != NULL && tmp == 0)
		{
			cmd_tab = cmd_to_tab(info, cmds[i]);
			if (search_exec(info, exec, cmds[i], cmd_tab))
				return (1);
		}
		else
			empty_pipe(exec, info);
		r_fd(exec);
	}
	return (0);
}

/*
This function initialize all the values of our t_exec structure
*/
static int	init_exec(t_info *info, t_exec *exec)
{
	exec->final_execstat = -1;
	exec->fd_list = ft_lstintnew(-2, &info->exec_mem);
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
	if (start_exec(info, &exec, 0))
		return ;
	wait_close(&exec, info->com_count - 1);
	stock_free(&info->exec_mem);
	return ;
}
