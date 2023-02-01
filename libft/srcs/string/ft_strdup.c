/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:55:26 by cpapot            #+#    #+#             */
/*   Updated: 2022/11/30 12:05:11 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	result = malloc(sizeof(char) * (len + 1));
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
