/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/27 23:32:06 by cpapot           ###   ########.fr       */
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
