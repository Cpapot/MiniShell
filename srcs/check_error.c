/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:06:38 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/20 18:16:48 by cpapot           ###   ########.fr       */
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

int	is_command_valid(t_list *lst)
{
	while (lst)
	{
		if (is_redirection(lst->content)
			&& (lst->next == NULL || is_text(lst->next->content)))
			return (print_error(ERROR5), 1);
		lst = lst->next;
	}
	return (0);
}
