/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:31:14 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/21 17:45:37 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

static int	export_parsing(char *str, t_info *info)
{
	if (str == NULL || ft_strcmp(str, ""))
		return (2);
	
}

int	export(char *str)
{
	int	parsing_res;

	parsing_res = export_parsing(str);
	if (parsing_res == 0)
		return (0);
	if (parsing_res == 2)
	{
		print_env(info->envp);
		return (1);
	}
}
