/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/09 01:15:08 by cpapot           ###   ########.fr       */
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
	info->prompt_mem = NULL;
	info->final_memparse = NULL;
	info->is_finish = 0;
	signal(SIGINT, catch_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	close_minishell(t_info	*info, int status)
{
	rl_clear_history();
	stock_free(&info->envp_mem);
	stock_free(&info->exec_mem);
	stock_free(&info->parsing);
	stock_free(&info->final_memparse);
	stock_free(&info->prompt_mem);
	exit(status);
}

void	loop(t_info *info)
{
	while (42)
	{
		prompt(info);
		info->final_parse = parsing(info);
		if (info->is_finish != 0)
			break ;
		if (info->final_parse != NULL)
		{
			// printtest(info);
					execution(info);
		}
		if (info->is_finish != 0)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;

	minishell_init(&info, argc, argv, envp);
	loop(&info);
	close_minishell(&info, 0);
}
