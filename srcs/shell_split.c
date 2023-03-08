/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:47:51 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/08 16:58:41 by cpapot           ###   ########.fr       */
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
	while ((str[u] != ' ' && str[u] && str[u + 1] != '\'' && str[u + 1] != '\"'))
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
	int		u;

	if (ft_strncmp(tmp, "\"", ft_strlen(tmp)) == 0)
		u = quote_size(str, 1);
	else if (ft_strncmp(tmp, "\'", ft_strlen(tmp)) == 0)
		u = quote_size(str, 0);
	else
		u = word_len(str);
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
		u = splited_word(str, tmp);
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
