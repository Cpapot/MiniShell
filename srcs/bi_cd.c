/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:19:03 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/07 14:54:49 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define CDERROR1	"cd: too many arguments"
#define CDERROR2	"cd: error while moving file"

int	count_args(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	bi_cd(t_list *lst, t_info *info)
{
	int	size;

	set_exitstatus(0);
	size = count_args(lst);
	if (size == 0 || lst->content == NULL)
	{
		if (chdir(ft_getenv("HOME", info->envp, & info->exec_mem)) == -1)
			return (ft_error(ERROR20, info), set_exitstatus(1), -1);
		return (1);
	}
	if (size > 1)
		return (ft_error(CDERROR1, info), set_exitstatus(1), -1);
	if (chdir(lst->content) == -1)
		return (ft_error(ERROR20, info), set_exitstatus(1), -1);
	return (1);
}
