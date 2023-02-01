/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:43:00 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/18 20:05:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_fd.h"

ssize_t	ft_putstr_len(int fd, char *str)
{
	ssize_t	len;

	if (str == NULL)
		return (ft_putnull_len(fd));
	len = write(fd, str, ft_strlen(str));
	return (len);
}
