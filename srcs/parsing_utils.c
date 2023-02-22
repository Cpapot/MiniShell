/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:51:08 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/22 17:46:48 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		count_commands_world(t_info *info, int i)
{
	t_list		*lst;
	char		*tmp;

	i = 0;
	lst = *info->command;
	while (lst)
	{
		tmp = (char *)lst->content;
		i++;
		if (tmp[0] == '|' && tmp[1] == 0)
			return (i);
		lst = lst->next;
	}
	return (i);
}

t_list	*skip_last_world(t_info *info, int i)
{
	t_list		*tmp;
	int			u;

	u = 0;
	tmp = *info->command;
	if (i)
	{
		while (u != i)
		{
			tmp = tmp->next;
			u++;
		}
	}
	return (tmp);
}

char	**split_command(t_info *info)
{
	char		**strs;
	static int	i = 0;
	int			u;
	t_list		*tmp;

	tmp = skip_last_world(info, i);
	i = count_commands_world(info, i);
	u = 0;
	strs = stock_malloc(sizeof(char *) * (i + 1), &info->parsing);
	while (u != i)
	{
		strs[u] = ft_strdup(tmp->content, &info->parsing);
		tmp = tmp->next;
		u++;
	}
	if (tmp == NULL)
		i = 0;
	strs[u] = NULL;
	return (strs);
}
