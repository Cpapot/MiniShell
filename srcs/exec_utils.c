/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 06:12:28 by mgagne            #+#    #+#             */
/*   Updated: 2023/05/13 19:50:11 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (envp[i])
	{
		splitted = ft_split((envp[i] + 5), ':', &info->exec_mem);
		if (!splitted)
			return (ft_error(ERROR99, info), NULL);
		return (splitted);
	}
	return (NULL);
}

static char	*check_path(t_info *info, char *path, t_memlist **mem, char *cmd)
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

	if (path)
	{
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
			return (stock_free(&mem), ft_error(ERROR2, info), NULL);
		res = ft_strdup(str, &info->exec_mem);
		if (!res)
			return (stock_free(&mem), ft_error(ERROR99, info), NULL);
		return (stock_free(&mem), res);
	}
	return (NULL);
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
	if (!result)
		return (NULL);
	j = 0;
	while (lst && lst->content)
	{
		result[j] = ft_strdup(lst->content, &info->exec_mem);
		if (!result[j])
			return (NULL);
		lst = lst->next;
		j++;
	}
	result[j] = NULL;
	return (result);
}



int	contains_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
