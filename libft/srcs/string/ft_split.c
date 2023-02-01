/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:35:50 by cpapot            #+#    #+#             */
/*   Updated: 2022/11/30 12:05:08 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*ft_next_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	return (&str[i]);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*result;
	int		len;
	size_t	i;

	i = 0;
	if (ft_strlen(s1) < n)
		return (NULL);
	result = malloc(sizeof(char) * (n + 1));
	if (result == 0)
		return (NULL);
	while (i != n)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	ft_count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == c)
		count--;
	while (str[i] != '\0')
	{
		if (str[i] == c && (!((str[i + 1] == c))
				&& str[i + 1] != '\0'))
			count++;
		i++;
	}
	if (str[0] != '\0' || c == '\0')
		count++;
	return (count);
}

static char	**ft_free_malloc(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		word_count;
	int		word_len;
	int		i;
	char	**result;

	if (!str)
		return (NULL);
	i = 0;
	word_len = 0;
	word_count = ft_count_word(str, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	while (i != word_count)
	{
		str = ft_next_char((char *)&str[word_len], c);
		word_len = 0;
		while (str[word_len] != c && str[word_len])
			word_len++;
		result[i] = ft_strndup(str, word_len);
		if (!result[i++])
			return (ft_free_malloc(result));
	}
	result[i] = NULL;
	return (result);
}
