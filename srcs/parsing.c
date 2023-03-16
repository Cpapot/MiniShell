/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/16 16:20:22 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cpy_final_parse(t_commands command, t_info *info)
{
	while (command.command)
	{
		command.command->content = ft_strdup(command.command->content,
				&info->final_memparse);
		command.command = command.command->next;
	}
	while (command.dir)
	{
		command.dir->dest = ft_strdup(command.dir->dest,
				&info->final_memparse);
		command.dir->type = ft_strdup(command.dir->type,
				&info->final_memparse);
		command.dir = command.dir->next;
	}
}

static t_list	*go_next_redirection(t_list *lst)
{
	while (lst->next && !is_redirection(lst->next->content))
		lst = lst->next;
	return (lst);
}

/*
 *This function takes in a linked list lst of parsed command arguments,
 *along with a pointer to a t_info struct and an integer id. It searches and
 *delete for any redirection tokens (e.g. <, >) within lst and creates a new
 *linked list dir of t_dir nodes, where each node represents a redirection and
 *contains the relevant input/output filepaths.
*/
t_list	*find_redirection(t_list *lst, t_info *info, int id)
{
	t_dir	*dir;
	t_list	*tmp;

	tmp = lst;
	dir = ft_lstdirnew(NULL, NULL, &info->final_memparse);
	if (is_redirection(lst->content))
	{
		ft_lstdiradd_back(&dir, ft_lstdirnew(lst->content,
				lst->next->content, &info->final_memparse));
		tmp = lst->next->next;
	}
	while (lst)
	{
		lst = go_next_redirection(lst);
		if (lst->next && is_redirection(lst->next->content))
		{
			ft_lstdiradd_back(&dir, ft_lstdirnew(lst->next->content,
					lst->next->next->content, &info->final_memparse));
			lst->next = lst->next->next->next;
		}
		else
			lst = lst->next;
	}
	info->final_parse[id].dir = dir->next;
	return (tmp);
}

/*
 *This function takes in a t_info struct pointer info and performs parsing
 *of the command string in info->prompt_string. It returns a pointer to a
 *t_commands struct, which contains an array of parsed commands and their
 *redirections
*/
t_commands	*parsing(t_info *info)
{
	t_list		*lst;
	t_commands	*result;
	int			i;

	i = 0;
	if (ft_strlen(info->prompt_string) == 0)
		return (NULL);
	lst = shell_split(info->prompt_string, &info->parsing);
	if (is_command_valid(lst))
		exit(1);
	result = split_pipe(info, lst);
	info->final_parse = result;
	while (result[i].command != NULL)
	{
		result[i].command
			= find_redirection(result[i].command, info, i);
		swap_env(result[i].command, info);
		remove_quote(result[i].command, &info->parsing);
		result[i].command = remove_empty_node(result[i].command);
		cpy_final_parse(result[i], info);
		i++;
	}
	stock_free(&info->parsing);
	return (result);
}
