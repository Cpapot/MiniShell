/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:47 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/24 16:08:47 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_info *info)
{
	stock_free(&info->parsing);
}

void	print_error(t_info *info, char *error)
{
	ft_printf_fd(2, RED"%s\n"WHITE, error);
	free_all(info);
	exit(1);
}
