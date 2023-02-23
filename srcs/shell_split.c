/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/23 14:13:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_word(char const *str)
{
	int		i;
	int		count;
	char	*c;

	i = 0;
	count = 0;
	if (str[0] == c)
		count--;
	while (str[i] != '\0')
	{
		if (str[i] == c && (!((str[i + 1] == c))
				&& str[i + 1] != '\0'))
			count++;
		if ((str[i] == '<' || str[i] == '>') &&
			(!str[i + 1] == '<' && !str[i + 1] == '>'))
			count++;
		i++;
	}
	if (str[0] != '\0' || c == '\0')
		count++;
	return (count);
}

static char	*ft_next_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}

static char	*ft_strndup(const char *s1, size_t n, t_memlist **stock)
{
	char	*result;
	int		len;
	size_t	i;

	i = 0;
	if (ft_strlen(s1) < n)
		return (NULL);
	result = stock_malloc(sizeof(char) * (n + 1), stock);
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
/*
split this: "echo test<<salut hey"
to:
echo
test
<<
salut
hey
*/

char	**shell_split(char *str, t_memlist)
{
	int		word_len;
	int		i;
	char	**result;
	char	**result;

	if (!str)
		return (NULL);
		i = 0;
	word_len = 0;
	word_count = ft_count_word(str, c);
	result = stock_malloc(sizeof(char *) * (word_count + 1), stock);
	if (!result)
		return (NULL);
	while (i != word_count)
	{
		str = ft_next_char((char *)&str[word_len], c);
		word_len = 0;
		while ((str[word_len] != ' ' && str[word_len]) ||)
			word_len++;
		result[i] = ft_strndup(str, word_len, stock);
		if (!result[i++])
			return (stock_free(stock), NULL);
	}
	result[i] = NULL;
	return (result);
}
