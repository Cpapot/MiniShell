/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/29 14:55:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_size_env(char *str, int mode)
{
	int			i;

	i = 0;
	if (!str[0])
		return (0);
	if (mode == 0)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i + 1);
	}
	else if (mode == 1)
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		return (i + 1);
	}
	return (0);
}

/*
	This function copy the final parsing in to a new memlist
*/
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

	i = -1;
	lst = shell_split(info, info->prompt_string, &info->parsing);
	if (lst == NULL || ft_strcmp("", lst->content) || is_line_valid(lst, info))
		return (NULL);
	result = split_pipe(info, lst);
	if (result == NULL)
		return (NULL);
	info->final_parse = result;
	while (result[++i].command != NULL)
	{
		result[i].command
			= find_redirection(result[i].command, info, i);
		swap_env(result[i].command, info, info->envp);
		remove_quote(result[i].command, &info->parsing);
		result[i].command = remove_empty_node(result[i].command);
		cpy_final_parse(result[i], info);
	}
	stock_free(&info->parsing);
	return (result);
}
