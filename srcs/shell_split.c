/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/04 17:13:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
static int	count_word(char const *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str[0] == ' ')
		count--;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && (!((str[i + 1] == ' '))
				&& str[i + 1] != '\0'))
			count++;
		if ((str[i] == '<' || str[i] == '>')
			&& (str[i + 1] != '<' && str[i + 1] != '>'))
			count++;
		if (str[i] == '|')
			count++;
		if ((str[i] != '<' && str[i] != '>' && str[i] != ' ')
			&& (str[i + 1] == '<' || str[i + 1] == '>'))
			count++;
		i++;
	}
	if (str[0] != '\0')
		count++;
	return (count);
}
*/

static int	count_word(char const *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && i++ > 0)
			count++;
		if ((str[i] == '<' || str[i] == '>') && count++ > 0)
		{
			while (str[i] == '<' || str[i] == '>')
				i++;
		}
		else if (str[i] != ' ')
		{
			count++;
			while (str[i] != ' ' && str[i] != '\0'
				&& str[i] != '|' && str[i] != '<' && str[i] != '>')
				i++;
		}
		else
			i++;
	}
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

static int	word_len(char *str)
{
	int	u;

	u = 0;
	while ((str[u] != ' ' && str[u]))
	{
		if (u == 0 && (str[u] == '<' || str[u] == '>'))
		{
			while ((str[u] == '<' || str[u] == '>' || str[u] == '>')
				&& str[u] != '|')
				u++;
			break ;
		}
		if (str[u] == '<' || str[u] == '>')
			break ;
		u++;
		if (str[u - 1] == '|' || (str[u] == '|'))
			break ;
	}
	return (u);
}

char	**shell_split(char *str, t_memlist **stock)
{
	int		u;
	int		i;
	char	**result;
	int		word_count;

	if (!str)
		return (NULL);
	i = 0;
	u = 0;
	word_count = count_word(str);
	result = stock_malloc(sizeof(char *) * (word_count + 1), stock);
	if (!result)
		return (NULL);
	while (i != word_count)
	{
		str = ft_next_char((char *)&str[u]);
		u = word_len(str);
		result[i] = ft_strndup(str, u, stock);
		if (!result[i++])
			return (stock_free(stock), NULL);
	}
	result[i] = NULL;
	return (result);
}
