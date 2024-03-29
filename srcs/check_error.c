/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:06:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/06/05 15:55:16 by mgagne           ###   ########.fr       */
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
