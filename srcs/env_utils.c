/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:43:39 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/05 16:17:48 by cpapot           ###   ########.fr       */
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

char	*start(char *str, int size, t_info *info)
{
	char	*result;

	result = ft_strdup(str, &info->parsing);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	return (result);
}

char	**set_endstartenv(char **parsedenv, t_info *info, int index, int end)
{
	int	i;
	int	u;

	u = 0;
	i = end;
	if (info->tmp_string[i] != ' ')
	{
		while (parsedenv[u + 1])
			u++;
		parsedenv[u] = ft_strjoin(parsedenv[u], &info->tmp_string[i], \
		&info->parsing);
		if (!parsedenv[u])
			ft_error(ERROR99, info);
	}
	if (index != 0 && info->tmp_string[index - 1] != ' ')
	{
		parsedenv[0] = ft_strjoin(start(info->tmp_string, index, info), \
		parsedenv[0], &info->parsing);
		if (!parsedenv[0])
			ft_error(ERROR99, info);
	}
	else
		info->tmp_string = parsedenv[0];
	return (parsedenv);
}

char	**empty_tab(t_info *info)
{
	char	**result;

	result = stock_malloc(2 * sizeof(char *), &info->parsing);
	if (!result)
		ft_error(ERROR99, info);
	result[0] = ft_strdup("", &info->parsing);
	if (!result[0])
		ft_error(ERROR99, info);
	result[1] = NULL;
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
