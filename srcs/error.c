/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:33:31 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/19 19:45:25 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	This function print the error and set the exit status or close minishell.
*/
void	ft_error(const char *error, t_info *info)
{
	ft_printf_fd(2, "%s\n", error);
	if (ft_strcmp(error, ERROR99) || ft_strcmp(error, ERROR98))
		close_minishell(info, 1);
	else
	{
		if (ft_strcmp(error, ERROR2) || ft_strcmp(error, ERROR20))
			set_exitstatus(127);
		else if (ft_strcmp(error, ERROR3) || ft_strcmp(error, ERROR5) \
			|| ft_strcmp(error, ERROR4) || ft_strcmp(error, ERROR6))
			set_exitstatus(2);
		else if (ft_strcmp(error, ERROR14) || ft_strcmp(error, ERROR15)
			|| ft_strcmp(error, EXPORTERROR1) || ft_strcmp(error, UNSETERROR1))
			set_exitstatus(1);
	}
}
