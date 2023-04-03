/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:20:54 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/03 17:47:00 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *this function redirects to the right builtins it returns 1 if it has found
 *and executed a builtins it returns 0 if the builtins does not exist and
 *returns -1 if there is an error
*/
int		find_builtins(t_list *lst, t_info *info, int out_fd)
{
	int	i;

	i = 0;
	if (ft_strcmp("export", lst->content))
		i = bi_export(lst->next->content, info);
	else if (ft_strcmp("echo", lst->content))
		i = bi_echo(lst->next, out_fd);
	else if (ft_strcmp("env", lst->content))
		i = bi_env(lst->next, info);
	else if (ft_strcmp("pwd", lst->content))
		i = bi_pwd(info, out_fd);
	else if (ft_strcmp("cd", lst->content))
		i = bi_cd(lst->next, info);
	else if (ft_strcmp("exit", lst->content))
		i = bi_exit(lst->next, info);
	return (i);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}
