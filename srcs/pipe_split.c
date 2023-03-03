/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:17:18 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/03 19:12:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	com_count(t_list *lst)
{
	int	result;

	result = 0;
	while (lst)
	{
		if (lst->content == "|")
			result++;
		lst = lst->next;
	}
	return (result + 1);
}

static t_list	*first_command(t_list *lst)
{

}

static t_fd	set_start_fd(void)
{
	t_fd	result;

	result.stderr = 2;
	result.stdin = 0;
	result.stdout = 1;
	return (fd);
}

static	t_list	*go_next_cmd(t_list *lst)
{

}

t_commands	*split_pipe(t_info *info,t_list *lst)
{
	int			i;
	int			count;
	t_list		*tmp;
	t_commands	*result;

	i = 0;
	tmp = lst;
	count = com_count(result);
	result = stock_malloc(sizeof(t_commands) * (count + 1), &info->parsing);
	if (result == NULL)
		print_error(info, "Memory error");
	while (i != count)
	{
		(result[i]).fd = set_start_fd();
		*(result[i]).command = first_command(tmp);
		tmp = go_next_cmd(tmp);
		if (i != 0)
			(result[i]).fd.stdin = (result[i - 1]).fd.stdout;
		i++;
	}
	return (result);
}
