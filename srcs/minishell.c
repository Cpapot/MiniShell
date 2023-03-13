/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/13 14:02:36 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info, int argc, char **argv)
{
	//signal(SIGINT, catch_signals);
	(void)argc;
	(void)argv;
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
		printf("\nCommande %d :\n", i + 1);
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

static void	prompt(t_info *info)
{
	/*while (1)
	{
		info->prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (strlen(info->prompt_string) != 0)
			break ;
	}*/
	info->prompt_string = ft_strdup("salut >>ya | uwu slt|oui >ok >ko| wc", &info->parsing);
	addto_logs(info->prompt_string, info);
}
/*
int	main(void)
{
	t_info		info;

	minishell_init(&info);

		prompt(&info);
		info.final_parse = parsing(&info);

	close_minishell(&info);
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	minishell_init(&info, argc, argv);

		prompt(&info);
		info.final_parse = parsing(&info);
		execution(&info, envp);

	close_minishell(&info);
}
