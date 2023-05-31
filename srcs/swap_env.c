/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:54:59 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/31 16:31:10 by cpapot           ###   ########.fr       */
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

char	*swap_envin_quote(char *str, t_info *info, char **envp, int *index)
{
	*index = *index + 1;
	while (str && str[*index])
	{
		if (str[*index] == '\"')
			break;
		else if (str[*index] == '$' && str[*index + 1] == '\"')
		{
			*index = *index + 1;
			return (str);
		}
		else if (str[*index] == '$')
		{
			if (is_contain_env(&str[*index]) == 1 && str[*index + 1] != '\"')
				str = swap_envstr(str, info, envp, index);
			else if (is_contain_env(&str[*index]) == 2 && str[*index + 1] != '\"')
				str = swap_exit(str, info, index);
		}
		*index = *index + 1;
	}
	return (str);
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
		parsedenv[u] = ft_strjoin(parsedenv[u], &info->tmp_string[i], &info->parsing);
		if (!parsedenv[u])
			ft_error(ERROR99, info);
	}
	if (index != 0 && info->tmp_string[index - 1] != ' ')
	{
		parsedenv[0] = ft_strjoin(start(info->tmp_string, index, info), parsedenv[0], &info->parsing);
		if (!parsedenv[0])
			ft_error(ERROR99, info);
	}
	else
		info->tmp_string = parsedenv[0];
	return (parsedenv);
}

char	**parse_env(char *str, t_info *info, char **envp, int index)
{
	char	**result;
	char	*env;
	int		i;

	i = index + 1;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\''
		&& str[i] != '\"' && str[i - 1] != '?')
		i++;
	if (str[index + 1] != '?' && i != index + 1)
		env = getenv_instr(&str[index + 1], i - index - 1, info, envp);
	else if (str[index + 1] && str[index + 1] == '?'  && i != index + 1)
		env = ft_itoa(get_exitstatus());
	else
		env = ft_strdup("$", &info->parsing);
	result = ft_split(env, " \t", &info->parsing);
	if (!result)
		ft_error(ERROR99, info);
	info->tmp_string = str;
	result = set_endstartenv(result, info, index, i);
	return (result);
}

char	*swap_env_parsed(t_list *lst, t_info *info, char **envp, int *index)
{
	int		i;
	t_list	*next;
	char	**parsedenv;

	i = 1;
	next = lst->next;
	lst->next = NULL;
	parsedenv = parse_env(lst->content, info, envp, *index);
	lst->content = parsedenv[0];
	while (parsedenv[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(parsedenv[i], &info->final_memparse));
		i++;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = next;
	return (parsedenv[0]);
}

/*
	If the command contains any env, this function will find and replace it
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
			else if (str[i] == '\"')
				str = swap_envin_quote(str, info, envp, &i);
			else if (str[i] == '$')
				str = swap_env_parsed(lst, info, envp, &i);
			i++;
		}
		lst->content = str;
		lst = lst->next;
	}
}
