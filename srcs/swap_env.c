/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:54:59 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/16 02:53:14 by cpapot           ###   ########.fr       */
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
		print_error(info, ERROR99);
	while (i != size)
	{
		env[i] = str[i];
		i++;
	}
	env[i] = '\0';
	result = getenv(env);
	if (result == NULL)
		result = ft_strdup("", &info->parsing);
	if (result == NULL)
		print_error(info, ERROR99);
	free (env);
	return (result);
}

static char	*return_start(char *str, int size, t_info *info)
{
	char	*result;

	result = ft_strdup(str, &info->parsing);
	if (result == NULL)
		print_error(info, ERROR99);
	result[size] = '\0';
	return (result);
}

static char	*swap_envstr(char *str, t_info *info)
{
	int		i;
	int		u;
	char	*tmp;
	char	*buff;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			i += quote_size(&str[i], 0);
		else if (str[i] == '$')
		{
			u = ++i;
			while (str[u] && str[u] != ' ' && str[u] != '$' && str[u] != '\''
				&& str[u] != '\"')
				u++;
			buff = getenv_instr(&str[i], u - i, info);
			tmp = ft_strjoin(buff, &str[u], &info->parsing);
			str = ft_strjoin(return_start(str, i - 1, info),
					tmp, &info->parsing);
			i += ft_strlen(buff) - 1;
		}
	}
	return (str);
}

void	swap_env(t_list *lst, t_info *info)
{
	while (lst)
	{
		if (is_contain_env(lst->content))
			lst->content = swap_envstr(lst->content, info);
		lst = lst->next;
	}
}
