/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:23:37 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/29 15:45:48 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define	ENVERROR	"No such file or directory"

int	bi_env(t_list *lst, t_info *info)
{
	if (lst != NULL || lst->content != NULL)
		return (print_error(ENVERROR), -1);
	else
		return (print_env(info->envp), 1);
	return ;
}
