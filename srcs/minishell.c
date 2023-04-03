/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/03 17:10:44 by cpapot           ###   ########.fr       */
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
	exit(status);
}

static void	prompt(t_info *info)
{
	while (1)
	{
		info->prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (info->prompt_string == NULL)
			close_minishell(info, 0);
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
			printtest(info);
			//execution(info);
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
