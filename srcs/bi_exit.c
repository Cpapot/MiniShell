/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:15:18 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/06 13:23:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' && str[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int		bi_exit(t_list *lst, t_info *info)
{
	int	status;

	status = ft_atoll(lst->content);
	printf("exit\n");
	if (ft_lstsize(lst) == 0)
		close_minishell(info, 0);
	if (ft_lstsize(lst) > 1)
		return (ft_error("too many arguments", info), -1);
	if (check_numeric(lst->content))
	{
		ft_error("numeric argument required", info);
		exit (2);
	}
	exit (status);
	return (1);
}
