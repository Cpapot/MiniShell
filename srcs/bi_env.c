/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:23:37 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 19:36:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	bi_env(t_list *lst, t_info *info, int fd)
{
	while (lst)
	{
		if (!ft_strcmp(lst->content, "env"))
			return (ft_error(ERROR20, info), -1);
		lst = lst->next;
	}
	return (set_exitstatus(0), print_env(info->envp, fd), 1);
}
