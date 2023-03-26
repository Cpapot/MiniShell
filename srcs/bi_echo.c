/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:09:34 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/26 18:52:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_flag(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	bi_echo(t_list *lst, int out_fd)
{
	int	is_nl;

	is_nl = 1;
	while (lst && check_flag(lst->content))
	{
		is_nl = 0;
		lst = lst->next;
	}
	while (lst)
	{
		ft_printf_fd(out_fd, "%s", lst->content);
		lst = lst->next;
		if (lst)
			ft_printf_fd(out_fd, " ");
	}
	if (is_nl == 1)
		ft_printf_fd(out_fd, "\n");
	return ;
}
