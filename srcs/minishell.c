/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:15:15 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/15 18:05:06 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prompt(t_info *info)
{
	//c'est un test
	info->prompt_string = ft_strdup("cdd -n -c   tdest alrd");
}

void	minishell_init(t_info *info)
{
	info->parsing = NULL;
}

int	main(void)
{
	t_info	info;
	t_list	*lst;

	prompt(&info);
	minishell_init(&info);
	lexer(&info);
	lst = *info.command;
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
	free(info.prompt_string);
	stock_free(&(info.parsing));
}
