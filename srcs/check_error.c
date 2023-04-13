/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:06:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/13 13:27:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_text(char *str)
{
	if (str == NULL)
		return (1);
	if (is_redirection(str))
		return (1);
	if (ft_strcmp("|", str))
		return (1);
	if (ft_strcmp("", str))
		return (1);
	return (0);
}

int	is_line_valid(t_list *lst, t_info *info)
{
	while (lst)
	{
		if (is_redirection(lst->content)
			&& (lst->next == NULL || is_text(lst->next->content)))
			return (ft_error(ERROR5, info), 1);
		lst = lst->next;
	}
	return (0);
}

int	is_command_line(t_list *lst, t_info *info)
{
	if (lst != NULL && lst->content != NULL && lst->content[0] == '/')
		return (ft_error(ERROR7, info), 0);

	return (1);
}
