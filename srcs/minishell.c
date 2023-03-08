/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/08 17:47:01 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info)
{
	info->parsing = NULL;
}

void	close_minishell(t_info	*info)
{
	t_commands	*result;
	t_list		*tmp;
	t_dir		*tmp2;
	int			i;

	i = 0;
	result = info->final_parse;
	while (result[i].command != NULL)
	{
		tmp = (result[i]).command;
		printf("\nCommande %d :\n", i);
		while (tmp)
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
	stock_free(&info->parsing);
}

int	main(void)
{
	t_info		info;

	minishell_init(&info);
	/*while (1)
	{
		info.prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (strlen(info.prompt_string) != 0)
			break ;
	}*/
	info.prompt_string = ft_strdup("salut |>>ya slt|oui >ok >ko|alo rs", &info.parsing);
	info.final_parse = parsing(&info);

	close_minishell(&info);
}
