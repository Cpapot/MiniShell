/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:21:09 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/09 01:00:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	printtest(t_info *info)
{
	t_list		*tmp;
	t_dir		*tmp2;
	t_commands	*result;
	int			i;

	i = 0;
	result = info->final_parse;
	while (i + 1 < info->com_count)
	{
		tmp = (result[i]).command;
		printf("\nCommande %d :\n", i + 1);
		if (tmp == NULL)
			printf("(null)");
		while (tmp && tmp->content)
		{
			printf("%s ", tmp->content);
			tmp = tmp->next;
		}
		printf("\n\n");
		tmp2 = (result[i]).dir;
		while (tmp2)
		{
			printf("%s %s	", tmp2->type, tmp2->dest);
			tmp2 = tmp2->next;
		}
		i++;
	}
}
