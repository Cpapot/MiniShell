/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:20:54 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/07 18:08:40 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *this function redirects to the right builtins it returns 1 if it has found
 *and executed a builtins it returns 0 if the builtins does not exist and
 *returns -1 if there is an error
*/
int	find_builtins(t_list *lst, t_info *info, int out_fd)
{
	int	i;

	i = 0;
	if (ft_strcmp("export", lst->content))
		i = bi_export(lst->next, info);
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
	else if (ft_strcmp("unset", lst->content))
		i = bi_unset(lst->next, info);
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

void	print_export(char **envp, t_info *info)
{
	int		i;
	char	*var;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s", find_name(envp[i], info));
		if (envp[i][ft_strlen(find_name(envp[i], info))] == '=')
			printf("=");
		var = find_var(envp[i], info);
		if (var != NULL)
			printf("\"%s\"", var);
		printf("\n");
		i++;
	}
}

char	*find_name(char *str, t_info *info)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	result = ft_stsubstr(str, 0, i, &info->exec_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	return (result);
}

char	*find_var(char *str, t_info *info)
{
	int		i;
	int		u;
	char	*result;

	i = 0;
	while (str[i] && (i == 0 || str[i - 1] != '='))
		i++;
	if (str[i] == 0 && str[i - 1] != '=')
		return (NULL);
	u = i;
	while (str[i] && str[i] != '$')
		i++;
	if (i == u && str[i - 1] == '=')
		return (ft_strdup("", &info->exec_mem));
	if (i == u)
		return (NULL);
	result = ft_stsubstr(str, u, i, &info->exec_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	return (result);
}
