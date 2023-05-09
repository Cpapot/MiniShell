/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:15:18 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/09 18:51:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	ft_atoll_bool(const char *str, int *b)
{
	long long	result;
	long long	tmp;
	char		is_negative;

	while (*str == ' ')
		str++;
	is_negative = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + *str++ - '0';
		if (tmp < result)
		{
			*b = 0;
			if (is_negative)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		result = tmp;
	}
	if (is_negative)
		return (-result);
	return (result);
}

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (1);
		i++;
	}
	return (0);
}

int	bi_exit(t_list *lst, t_info *info)
{
	long long	status;
	int			b;

	b = 1;
	if (lst != NULL)
		status = ft_atoll_bool(lst->content, &b);
	else
		 status = 0;
	printf("exit\n");
	if (ft_lstsize(lst) == 0)
		close_minishell(info, 0);
	if (ft_lstsize(lst) > 1)
		return (set_exitstatus(1), ft_error("too many arguments", info), -1);
	if (check_numeric(lst->content) || b == 0)
	{
		ft_error("numeric argument required", info);
		exit (2);
	}
	exit (status);
	return (1);
}
