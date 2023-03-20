/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/20 18:16:59 by cpapot           ###   ########.fr       */
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

static int	word_len(char *str)
{
	int		u;

	u = 0;
	while ((str[u] != ' ' && str[u] && str[u] != '\''
			&& str[u] != '\"'))
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

static int	splited_word(char *str)
{
	int			i;
	int			buff;

	i = 0;
	buff = 0;
	while (str[i] && str[i] != ' ' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		if (str[i] == '\"')
		{
			i += quote_size(&str[i], 1);
			buff = 1;
		}
		else if (str[i] == '\'')
		{
			i += quote_size(&str[i], 2);
			buff = 1;
		}
		if (str[i] == 0)
			return (-1);
		i++;
	}
	if (buff == 0)
		i = word_len(str);
	return (i);
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
		u = splited_word(str);
		if (u == -1)
			return (print_error(ERROR3), NULL);
		tmp = ft_strndup(str, u, stock);
		if (!tmp)
			return (stock_free(stock), NULL);
		printf("%s ", tmp);
		ft_lstadd_back(&start, ft_lstnew(tmp, stock));
	}
	printf("\n\n");
	start = start->next;
	return (start);
}
