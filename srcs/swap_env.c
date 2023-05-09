/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:54:59 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/09 18:59:15 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_contain_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\"')
				return (0);
			if (str[i + 1] == 0 || str[i + 1] == ' ')
				break ;
			if (i > 0 && str[i - 1] == '\\')
				break ;
			if (str[i + 1] == '?')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*getenv_instr(char *str, int size, t_info *info, char **envp)
{
	char	*env;
	char	*result;
	int		i;

	i = 0;
	env = malloc((size + 1) + sizeof(char));
	if (env == NULL)
		return (NULL);
	while (i != size)
	{
		env[i] = str[i];
		i++;
	}
	env[i] = '\0';
	result = ft_getenv(env, envp, &info->parsing);
	if (result == NULL)
		result = ft_strdup("", &info->parsing);
	if (result == NULL)
		return (NULL);
	free (env);
	return (result);
}

char	*start(char *str, int size, t_info *info)
{
	char	*result;

	result = ft_strdup(str, &info->parsing);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	return (result);
}

char	*swap_envstr(char *str, t_info *info, char **envp, int *index)
{
	int		u;
	char	*tmp;
	char	*buff;

	u = *index + 1;
	while (str[u] && str[u] != ' ' && str[u] != '$' && str[u] != '\''
		&& str[u] != '\"')
		u++;
	buff = getenv_instr(&str[*index + 1], u - *index - 1, info, envp);
	tmp = ft_strjoin(buff, &str[u], &info->parsing);
	str = ft_strjoin(start(str, *index, info), tmp, &info->parsing);
	if (!buff || !tmp || !str)
		ft_error(ERROR99, info);
	*index += ft_strlen(buff) - 1;
	return (str);
}

/*
	If the command contains any env  , this function will find and replace it
*/
void	swap_env(t_list *lst, t_info *info, char **envp)
{
	int		i;
	char	*str;

	while (lst)
	{
		str = lst->content;
		i = 0;
		while (str && str[i])
		{
			if (str[i] == '\'')
				i += quote_size_env(&str[i], 0);
			else if (str[i] == '$')
			{
				if (is_contain_env(&str[i]) == 1)
					str = swap_envstr(str , info, envp, &i);
				else if (is_contain_env(&str[i]) == 2)
					str = swap_exit(str, info, &i);
			}
			i++;
		}
		lst->content = str;
		lst = lst->next;
	}
}
