/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:47 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/19 16:29:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_char_in_str(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getenv(char *env, char **envp, t_memlist **stock)
{
	int		i;
	int		u;

	i = 0;
	while (envp[i])
	{
		u = 0;
		while (envp[i][u] && envp[i][u] != '=')
			u++;
		if (ft_strcmp(env, ft_stsubstr(envp[i], 0, u, stock)))
			return (ft_stsubstr(envp[i], u + 1, ft_strlen(envp[i]), stock));
		i++;
	}
	return (NULL);
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
