/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:30:42 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/14 16:40:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_stsubstr(char const *s, unsigned int start, size_t len, t_memlist **st)
{
	char	*result;
	size_t	i;
	size_t	malloc_size;

	i = 0;
	if (len == 0 || start > ft_strlen(s))
	{
		result = stock_malloc(sizeof(char), st);
		result[0] = '\0';
		return (result);
	}
	if (start + len > ft_strlen(s))
		malloc_size = ft_strlen(s) - start;
	else
		malloc_size = (len);
	result = stock_malloc(sizeof(char) * malloc_size + 1, st);
	if (result == NULL)
		return (NULL);
	while (i != malloc_size)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}
