/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:54:17 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/03 17:08:19 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define PWDERROR "Error while calling \"getcwd\""

int	bi_pwd(t_info *info, int out_fd)
{
	char	*str;

	str = malloc(2048);
	if (str == NULL)
		print_error_exit(info, ERROR99, 0);
	if (getcwd(str, 2048) == NULL)
	{
		print_error(PWDERROR);
		return (free (str), -1);
	}
	ft_printf_fd(out_fd, "%s\n", str);
	free (str);
	return (1);
}

