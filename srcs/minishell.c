/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/04 18:54:23 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info)
{
	info->parsing = NULL;
	info->fd.stderr = 2;
	info->fd.stdin = 0;
	info->fd.stdout = 1;
}

void	close_minishell(t_info	*info)
{
	t_commands	*result;
	t_list		*tmp;
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
		printf("\nstdin : %d\n", result[i].fd.stdin);
		printf("stdout : %d\n", result[i].fd.stdout);
		printf("stderr : %d\n", result[i].fd.stderr);
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
	info.prompt_string = ft_strdup("salut|ok>>ya|oui >ok ko|alors", &info.parsing);
	info.final_parse = parsing(&info);
	close_minishell(&info);
}
