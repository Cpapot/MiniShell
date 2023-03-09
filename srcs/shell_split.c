/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/09 16:17:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_next_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}

static int	quote_size(char *str, int mode)
{
	int			i;

	i = 0;
	if (mode == 0)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
	else if (mode == 1)
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		return (i);
	}
	return (0);
}

static int	word_len(char *str)
{
	int			u;

	u = 0;
	if (str[0] == '\'' || str[0] == '\"')
		return (1);
	while ((str[u] != ' ' && str[u] && str[u + 1] != '\''
			&& str[u + 1] != '\"'))
	{
		if (u == 0 && (str[u] == '<' || str[u] == '>'))
		{
			while ((str[u] == '<' || str[u] == '>' || str[u] == '>')
				&& str[u] != '|' && str[u + 1] != '\'' && str[u + 1] != '\"')
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

static int	splited_word(char *str, char *tmp)
{
	int			u;
	static int	buff = 0;

	if (tmp && ft_strncmp(tmp, "\"", ft_strlen(tmp)) == 0 && buff % 2)
		u = quote_size(str, 1);
	else if (tmp && ft_strncmp(tmp, "\'", ft_strlen(tmp)) == 0 && buff % 2)
		u = quote_size(str, 0);
	else
	{
		u = word_len(str);
		if (ft_strncmp(str, "\"", ft_strlen(str))
			|| ft_strncmp(str, "\'", ft_strlen(str)))
			buff++;
	}
	return (u);
}

/*
 *The shell_split function takes in a string and a pointer to a memory
 *list. It then separates the string into individual words, based on
 *whitespace, quotes, and special characters such as redirection symbols
 *and pipes. The function returns a linked list of t_list structs, with
 *each node containing a pointer to a null-terminated string that
 *represents a single word.
*/
t_list	*shell_split(char *str, t_memlist **stock)
{
	int		u;
	char	*tmp;
	t_list	*start;

	if (!str)
		return (NULL);
	u = 0;
	start = ft_lstnew(NULL, stock);
	tmp = NULL;
	while (str[0])
	{
		str = ft_next_char((char *)&str[u]);
		u = splited_word(str, tmp);
		/*if (!str[u] && ft_strcmp(tmp, "\""))
			str = prompt_until_char('\"', stock, str);
		else if (!str[u] && ft_strcmp(tmp, "\'"))
			str = prompt_until_char('\"', stock, str);*/
		tmp = ft_strndup(str, u, stock);
		if (!tmp)
			return (stock_free(stock), NULL);
		printf("%s\n", tmp);
		ft_lstadd_back(&start, ft_lstnew(tmp, stock));
	}
	printf("\n\n");
	start = start->next;
	return (start);
}
