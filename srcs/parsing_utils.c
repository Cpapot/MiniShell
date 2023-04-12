/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:51:08 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/12 14:14:12 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	*prompt_until_char(char c, t_memlist **stock, char *str)
{
	char	*result;
	char	*tmp;
	int		i;

	tmp = str;
	while (42)
	{
		i = 0;
		result = readline(BLACK">"WHITE);
		while (result[i])
		{
			if (result[i] == c)
			{
				tmp = ft_strjoin(tmp, result, stock);
				return (tmp);
			}
			i++;
		}
		tmp = ft_strjoin(tmp, result, stock);
		tmp = ft_strjoin(tmp, NL, stock);
	}
}*/

char	*ft_strndup(const char *s1, size_t n, t_memlist **stock)
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

int	is_redirection(char *str)
{
	if (ft_strcmp(str, "<"))
		return (1);
	else if (ft_strcmp(str, "<<"))
		return (1);
	else if (ft_strcmp(str, ">"))
		return (1);
	else if (ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

t_dir	*ft_lstdirnew(char *type, char *dest, t_memlist **mem)
{
	t_dir	*node;

	node = stock_malloc(sizeof(t_dir), mem);
	if (node == NULL)
		return (NULL);
	node->type = type;
	if (dest != NULL)
		node->dest = remove_actual_quote(dest, mem);
	else
		node->dest = NULL;
	node->next = NULL;
	return (node);
}

void	ft_lstdiradd_back(t_dir **lst, t_dir *new)
{
	t_dir	*last;

	if (new == NULL || lst == NULL)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}
