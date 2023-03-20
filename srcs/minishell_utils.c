/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:47 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/20 19:03:52 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_info *info)
{
	rl_clear_history();
	stock_free(&info->parsing);
	stock_free(&info->final_memparse);
}

void	print_error_exit(t_info *info, char *error)
{
	ft_printf_fd(2, "\n%s\n", error);
	free_all(info);
	exit(1);
}

void	print_error(char *error)
{
	ft_printf_fd(2, "\n%s\n", error);
}
