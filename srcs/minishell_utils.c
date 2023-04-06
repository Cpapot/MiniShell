/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:07:47 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/06 18:50:58 by cpapot           ###   ########.fr       */
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

void	print_error_exit(t_info *info, char *error, int status)
{
	ft_printf_fd(2, "\n%s\n", error);
	close_minishell(info, status);
}

void	print_error(char *error)
{
	ft_printf_fd(2, "\n%s\n", error);
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
