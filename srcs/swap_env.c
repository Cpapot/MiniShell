/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:54:59 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/11 02:15:19 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_contain_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static char	*getenv_instr(char *str, int size, t_info *info)
{
	char	*env;
	char	*result;
	int		i;

	i = 0;
	env = malloc((size + 1) + sizeof(char));
	if (env == NULL)
		print_error(info, ERROR1);
	while (i != size)
	{
		env[i] = str[i];
		i++;
	}
	env[i] = '\0';
	result = getenv(env);
	free (env);
	return (result);
}

static char *return_start(char *str, int size, t_info *info)
{
	char	*result;
	result = ft_strdup(str, &info->parsing);
	if (result == NULL)
		print_error(info, ERROR1);
	result[size] = '\0';
	return (result);
}

static char	*swap_envstr(char *str, t_info *info)
{
	int		i;
	int		u;
	char	*result;
	char	*tmp;

	i = 0;
	result = str;
	while (result[i])
	{
		if (result[i] == '$')
		{
			i++;
			u = i;
			while (result[u] && result[u] != ' ' && result[u] != '$')
				u++;
			tmp = ft_strjoin(getenv_instr(&result[i], u, info), &result[u], &info->parsing);
			result = ft_strjoin(return_start(result, i - 1, info), tmp, &info->parsing);
			if (result == NULL)
				print_error(info, ERROR1);
			i = i + ft_strlen(tmp);
		}
		i++;
	}
	return (result);
}

void	swap_env(t_list *lst, t_info *info)
{
	char *tmp;

	tmp = ft_strdup(" ", &info->parsing);
	while (lst)
	{
		if (lst->next && !ft_strcmp(lst->next->content, "'") && !ft_strcmp(tmp, "'")
			&& is_contain_env(lst->content))
			lst->content = swap_envstr(lst->content, info);
		tmp = lst->content;
		lst = lst->next;
	}
}
