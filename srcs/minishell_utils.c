/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:47 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/16 02:54:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_info *info)
{
	stock_free(&info->parsing);
}

void	print_error(t_info *info, char *error)
{
	perror(error);
	free_all(info);
	exit(1);
}
