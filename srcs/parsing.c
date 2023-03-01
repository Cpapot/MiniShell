/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/28 22:53:21 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	**lexer(t_info *info)
{
	char	**split;
	t_list	*start;
	t_list	**result;
	int		i;

	start = NULL;
	i = 1;
	split = shell_split(info->prompt_string, &info->parsing);
	if (split == NULL)
		print_error(info, "Memory error");
	if (split[0] != NULL)
		start = ft_lstnew(split[0], &info->parsing);
	while (split[i] != NULL)
	{
		ft_lstadd_back(&start, ft_lstnew(split[i], &info->parsing));
		i++;
	}
	result = &start;
	return (result);
}

t_list	*find_redirection(t_list *lst, t_info *info)
{
	t_list	*tmp;
	int		index;

	tmp = lst;
	while (lst)
	{
		lst = tmp;
		index = 0;
		while (lst && lst->content[0] != '<'
			&& lst->content[0] != '>')
		{
			lst = lst->next;
			index++;
		}
		if (lst == NULL)
			break ;
		else if (!ft_strncmp(lst->content, ">", ft_strlen(lst->content)))
			lst = out_redirection(tmp, index, info);
		else if (!ft_strncmp(lst->content, "<", ft_strlen(lst->content)))
			lst = in_redirection(tmp, index, info);
        else if (!ft_strncmp(lst->content, ">>", ft_strlen(lst->content)))
            lst = out_double_redirection(tmp, index, info);
        else if (!ft_strncmp(lst->content, "<<", ft_strlen(lst->content)))
            lst = in_double_redirection(tmp, index, info);
	}
	lst = tmp;
	return (lst);
}

t_list	**parsing(t_info *info)
{
	t_list	**result;

	if (ft_strlen(info->prompt_string) == 0)
		return (NULL);
	result = lexer(info);
	//avant ca gerer les pipes et avoir une structure pour chaque commande et les quote
	*result = find_redirection(*result, info);
	return (result);
}
