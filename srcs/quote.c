/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:20:58 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/16 03:00:15 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*remove_actual_quote(char *str, t_memlist **stock)
{
	int			i;
	char		c;
	static int	save = 0;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			save++;
			str = ft_strjoin(ft_stsubstr(str, 0, i, stock), &str[i + 1], stock);
			if (save % 2)
			{
				if (c == '\'')
					i += quote_size(&str[i], 0);
				else
					i += quote_size(&str[i], 1);
			}
		}
		else
			i++;
	}
	return (str);
}

void	remove_quote(t_list *lst, t_memlist **stock)
{
	while (lst)
	{
		lst->content = remove_actual_quote(lst->content, stock);
		lst = lst->next;
	}
}

t_list	*remove_empty_node(t_list *lst)
{
	t_list	*start;
	t_list	*tmp;

	start = lst;
	tmp = NULL;
	while (lst && ft_strcmp("", lst->content))
	{
		start = lst->next;
		lst = lst->next;
	}
	while (lst)
	{
		if (tmp && lst && ft_strcmp("", lst->content))
		{
			tmp->next = lst->next;
			lst = tmp;
		}
		else
		{
			tmp = lst;
			lst = lst->next;
		}
	}
	return (start);
}

int	quote_size(char *str, int mode)
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
