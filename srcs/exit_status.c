/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:35 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 20:01:58 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		exit_status = 0;

void	set_exitstatus(int status)
{
	exit_status = status;
}

char	*swap_exit(char *str, t_info *info)
{
	int		i;
	int		u;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			i += quote_size(&str[i], 0);
		else if (str[i] == '$')
		{
			u = ++i;
			while (str[u] && str[u] != ' ' && str[u] != '$' && str[u] != '\''
				&& str[u] != '\"')
				u++;
			tmp = ft_strjoin(ft_itoa(exit_status), &str[u], &info->parsing);
			str = ft_strjoin(start(str, i - 1, info), tmp, &info->parsing);
			if (!tmp || !str)
				print_error_exit(info, ERROR99, EXIT_FAILURE);
			i += ft_strlen(ft_itoa(exit_status)) - 1;
		}
	}
	return (str);
}
