/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:17:18 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/02 17:22:26 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	com_count(t_list *lst)
{
	int	result;

	result = 0
	while (lst)
	{
		if (lst->content == "|")
			result++;
		lst = lst->next;
	}
	return (result + 1);
}

t_commands	*split_pipe(t_info *info,t_list *lst)
{
	int			i;
	int			count;
	t_list		*tmp;
	t_commands	*result;

	i = 0;
	count = com_count(result);
	result = stock_malloc(sizeof(t_commands) * (count + 1), &info->parsing);
	if (result == NULL)
		print_error(info, "Memory error");
	while (i != count)
	{

		while (command)
		i++;
		(result[i])->command = lst;
	}
}
