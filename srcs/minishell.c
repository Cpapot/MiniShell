/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/28 22:59:43 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info)
{
	info->parsing = NULL;
	info->lexer = NULL;
	info->fd.stderr = 2;
	info->fd.stdin = 0;
	info->fd.stdout = 1;
}

void	close_minishell(t_info	*info)
{
	t_list		*lst;

	if (info->prompt_string != NULL && info->command != NULL)
	{
		lst = *info->command;
		while (lst)
		{
			ft_printf("%s\n", lst->content);
			lst = lst->next;
		}
	}
	ft_printf("stdin :%d\n", info->fd.stdin);
	ft_printf("stdout :%d\n", info->fd.stdout);
	ft_printf("stderr :%d\n", info->fd.stderr);
    ft_printf_fd(info->fd.stdout, "sassslut\n");
	stock_free(&info->parsing);
	stock_free(&info->lexer);
}

int	main(void)
{
	t_info		info;

	minishell_init(&info);
	//info.prompt_string = ft_strdup("shhhes",&info.parsing);
	while (1)
	{
		info.prompt_string = readline(BLUE"Minishell $>"WHITE);
		if (strlen(info.prompt_string) != 0)
			break ;
	}
	info.command = parsing(&info);
	close_minishell(&info);
}
