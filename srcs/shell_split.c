/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/07 17:09:52 by cpapot           ###   ########.fr       */
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

static int	quote_size(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			i++;
		return (i);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\"')
			i++;
		return (i);
	}
}

static int	word_len(char *str)
{
	int	u;

	u = 0;
	if (str[0] == '\'' || str[0] == '\"')
		return (quote_size(str));
	while ((str[u] != ' ' && str[u] && str[u] != '\'' && str[u] != '\"'))
	{
		if (u == 0 && (str[u] == '<' || str[u] == '>'))
		{
			while ((str[u] == '<' || str[u] == '>' || str[u] == '>')
				&& str[u] != '|' && str[u] != '\'' && str[u] != '\"')
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

t_list	*shell_split(char *str, t_memlist **stock)
{
	int		u;
	char	*tmp;
	t_list	*start;

	if (!str)
		return (NULL);
	u = 0;
	start = ft_lstnew(NULL, stock);
	while (str[0])
	{
		str = ft_next_char((char *)&str[u]);
		u = word_len(str);
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
