/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:28 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/28 21:50:33 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*out_redirection(t_list	*lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		info->fd.stdout = -1;
	else
		info->fd.stdout = open(tmp->next->content, O_WRONLY);
	result->next = tmp->next->next;
	return (result);
}

t_list	*in_redirection(t_list	*lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		info->fd.stdin = -1;
	else
		info->fd.stdin = open(tmp->next->content, O_RDONLY);
	result->next = tmp->next->next;
	return (result);
}
