/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/28 17:41:07 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	**lexer(t_info *info)
{
	char	**split;
	t_list	*start;
	t_list	**result;
	int		i;

	i = 1;
	split = shell_split(info->prompt_string, &info->parsing);
	if (split == NULL)
		print_error(info, "Memory error");
	start = ft_lstnew(split[0], &info->parsing);
	while (split[i])
	{
		ft_lstadd_back(&start, ft_lstnew(split[i], &info->parsing));
		i++;
	}
	result = &start;
	return (result);
}

t_fd	find_redirection(t_list	**lst)
{
	t_fd	result;
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->content[0] != '<'
		&& tmp->content[0] != '>')
		tmp = tmp->next;
	if (!ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)))
		result = out_redirection(lst);
	return (result);
}

t_list	**parsing(t_info *info)
{
	t_list	**result;

	result = lexer(info);
	//avant ca gerer les pipes et avoir une structure pour chaque commande et les quote
	info->fd = find_redirection(result);
	return (result);
}
