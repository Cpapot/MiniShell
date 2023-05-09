/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:35 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/09 18:07:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_exit_status = 0;

void	set_exitstatus(int status)
{
	g_exit_status = status;
}

char	*swap_exit(char *str, t_info *info, int *index)
{
	int		u;
	char	*tmp;

	u = *index + 1;
	u++;
	tmp = ft_strjoin(ft_itoa(g_exit_status), &str[u], &info->parsing);
	str = ft_strjoin(start(str, *index, info), tmp, &info->parsing);
	if (!tmp || !str)
		ft_error(ERROR99, info);
	*index += ft_strlen(ft_itoa(g_exit_status)) - 1;
	return (str);
}
