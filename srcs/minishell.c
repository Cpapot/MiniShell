/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/21 17:04:57 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info, int argc, char **argv, char **envp)
{
	//signal(SIGINT, catch_signals);
	(void)argc;
	(void)argv;
	info->envp = envp;
	info->parsing = NULL;
	info->final_memparse = NULL;
}

void	close_minishell(t_info	*info)
{
	t_commands	*result;
	t_list		*tmp;
	t_dir		*tmp2;
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
	rl_clear_history();
	stock_free(&info->parsing);
	stock_free(&info->final_memparse);
}

static void	prompt(t_info *info)
{
	while (1)
	{
		info->prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (strlen(info->prompt_string) != 0)
			break ;
	}
	//info->prompt_string = ft_strdup("cat |cat shh << |", &info->parsing);
	addto_logs(info->prompt_string, info);
	add_history(info->prompt_string);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	minishell_init(&info, argc, argv, envp);
	while (42)
	{
		prompt(&info);
		info.final_parse = parsing(&info);
		if (info.final_parse != NULL)
			break ;
	}
	close_minishell(&info);
}
