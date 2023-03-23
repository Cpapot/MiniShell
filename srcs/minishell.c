/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/23 17:37:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info, int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
	info->lastprompt_string = NULL;
	info->envp = envp;
	info->parsing = NULL;
	info->final_memparse = NULL;
	info->envp_mem = NULL;
	info->exec_mem = NULL;
	info->final_memparse = NULL;
	signal(SIGINT, catch_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	close_minishell(t_info	*info)
{
	rl_clear_history();
	stock_free(&info->envp_mem);
	stock_free(&info->exec_mem);
	stock_free(&info->parsing);
	stock_free(&info->final_memparse);
	exit(1);
}

static void	prompt(t_info *info)
{
	while (1)
	{
		info->prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (info->prompt_string == NULL)
			close_minishell(info);
		if (strlen(info->prompt_string) != 0)
			break ;
	}
	//info->prompt_string = ft_strdup("\"\"\"\"", &info->parsing);
	if (info->lastprompt_string
		&& !ft_strcmp(info->lastprompt_string, info->prompt_string))
		add_history(info->prompt_string);
	addto_logs(info->prompt_string, info);
	info->lastprompt_string = info->prompt_string;
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
			printtest(&info);
	}
	close_minishell(&info);
}

