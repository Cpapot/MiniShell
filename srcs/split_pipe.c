/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:17:18 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/09 14:45:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	com_count(t_list *lst)
{
	int	result;

	result = 0;
	while (lst)
	{
		if (ft_strncmp("|", lst->content, ft_strlen(lst->content)) == 0)
			result++;
		lst = lst->next;
	}
	return (result + 1);
}

static t_list	*first_command(t_list *lst, t_info *info)
{
	t_list	*start;

	start = NULL;
	while (lst)
	{
		if (ft_strncmp("|", lst->content, ft_strlen(lst->content)) == 0)
			break ;
		if (start != NULL)
			ft_lstadd_back(&start, ft_lstnew(lst->content, &info->parsing));
		else
			start = ft_lstnew(lst->content, &info->parsing);
		lst = lst->next;
	}
	return (start);
}

static	void	go_next_cmd(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp("|", tmp->content, ft_strlen(tmp->content)) == 0)
		{
			(*lst) = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
}

/*
 *The split_pipe function is used to divide a linked list of commands into
 *multiple sublists, using the "|" symbol as a separator. This allows for
 *executing multiple commands in parallel using the shell pipe feature.
*/
t_commands	*split_pipe(t_info *info, t_list *lst)
{
	int			i;
	int			count;
	t_list		*tmp;
	t_commands	*result;

	i = -1;
	tmp = lst;
	count = com_count(tmp);
	result = stock_malloc(sizeof(t_commands) * (count + 1), &info->parsing);
	if (result == NULL)
		print_error(info, "Memory error");
	while (++i != count)
	{
		result[i].command = first_command(tmp, info);
		tmp = lst;
		go_next_cmd(&tmp);
		lst = tmp;
	}
	result[i].command = NULL;
	return (result);
}
