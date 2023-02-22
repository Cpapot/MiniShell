/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/22 17:52:35 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_init(t_info *info)
{
	info->parsing = NULL;
	info->lexer = NULL;
}

int	main(void)
{
	t_info	info;
	t_list	*lst;
	t_memlist	*qie;

	qie = NULL;
		//info.prompt_string = readline(BLUE"Minishell: "WHITE);
		info.prompt_string = ft_strdup("cdd -n -c   tdest alrd", &qie);
		minishell_init(&info);
		info.command = lexer(&info);
		lst = *info.command;
		while (lst)
		{
			ft_printf("%s\n", lst->content);
			lst = lst->next;
		}
		parser(&info);
		free(info.prompt_string);
		stock_free(&(info.parsing));
}
