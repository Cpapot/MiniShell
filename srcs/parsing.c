/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/13 20:12:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parsing(t_info *info)
{
	char	**split;
	t_list	*start;
	int		i;

	i = 1;
	split = ft_split(info->prompt_string, ' ', &info->parsing);
	if (split == NULL)
		print_error(info, "Memory error");
	start = ft_lstnew(split[0], &info->parsing);
	while (split[i])
	{
		ft_lstadd_back(&start, ft_lstnew(split[i], &info->parsing));
		i++;
	}
	info->command = &start;
}
