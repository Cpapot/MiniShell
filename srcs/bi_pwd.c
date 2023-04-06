/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:54:17 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/06 13:26:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define PWDERROR "Error while calling \"getcwd\""

int	bi_pwd(t_info *info, int out_fd)
{
	char	*str;

	str = malloc(2048);
	if (str == NULL)
		ft_error(ERROR99, info);
	if (getcwd(str, 2048) == NULL)
	{
		ft_error(PWDERROR, info);
		return (free (str), -1);
	}
	ft_printf_fd(out_fd, "%s\n", str);
	free (str);
	return (1);
}

