/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:26 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/22 16:40:52 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1, t_memlist **stock)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	result = stock_malloc(sizeof(char) * (len + 1), stock);
	if (result == 0)
		return (0);
	while (i != len)
	{
		result[i] = s1[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}
