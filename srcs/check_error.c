/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:06:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/16 16:49:30 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_text(char *str)
{
	if (is_redirection(str))
		return (1);
	if (ft_strcmp("|", str))
		return (1);
	return (0);
}

int	is_command_valid(t_list *lst)
{
	while (lst)
	{
		if (is_redirection(lst->content)
			&& ((lst->next != NULL && is_text(lst->next->content))))
		{
			perror(ERROR5);
			return (1);
		}
		lst = lst->next;
	}
	return (1);
}
