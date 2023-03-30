/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:36:14 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/30 14:13:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
This function gets the path String and checks wether or not the path given is
available to execute our commands with the access function
*/
char	*get_path(char **envp, t_memlist *exec)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	splitted = ft_split(envp[i], ':', &exec);
	i = 0;
	while (splitted[i])
	{
		if (access(splitted[i], F_OK))
			break;
		i++;
	}
	if (!splitted[i])
		return (stock_free(&exec), NULL);
	return (splitted[i]);

}
/*
This function handles all the execution process of the commands
*/
/*
void	execution(t_info *info, char **envp)
{
	t_memlist	*exec;
	char		*path;

	exec = NULL;
	path = get_path(envp, exec);
	return ;
}*/
