/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:31:14 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/05 16:06:26 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define EXPORTERROR1	"\e[31m\e[1mexport\e[0m: not a valid identifier"

static char	**add_to_envp(char **envp, char *name, char *var, t_info *info)
{
	int		i;
	char	**result;

	i = 0;
	while (envp[i])
		i++;
	result = stock_malloc(sizeof(char *) * (i + 2), &info->envp_mem);
	if (result == NULL)
		print_error_exit(info, ERROR99, 0);
	i = 0;
	while (envp[i])
	{
		result[i] = envp[i];
		i++;
	}
	result[i] = ft_strjoin(name, var, &info->envp_mem);
	if (result[i] == NULL)
		print_error_exit(info, ERROR99, 0);
	result[i + 1] = NULL;
	return (result);

}

char	*find_name(char *str, t_info *info)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && (i == 0 || str[i - 1] != '='))
		i++;
	result = ft_stsubstr(str, 0, i, &info->exec_mem);
	if (str == NULL)
		print_error_exit(info, ERROR99, 0);
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
	if (str[i] == 0)
	{
		result = ft_strdup("", &info->exec_mem);
		if (result == NULL)
			print_error_exit(info, ERROR99, 0);
		return (result);
	}
	u = i;
	while (str[i] && str[i] != '$')
		i++;
	result = ft_stsubstr(str, u, i, &info->exec_mem);
	if (result == NULL)
		print_error_exit(info, ERROR99, 0);
	return (result);
}

static int	export_parsing(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || ft_strcmp(str, ""))
		return (2);
	while (str[i] && str[i] != '=')
	{
		if (is_char_in_str(str[i], INV_ID_EXPORT))
			return (1);
		i++;
	}
	return (0);
}

int		bi_export(char *str, t_info *info)
{
	int	parsing_res;

	parsing_res = export_parsing(str);
	if (parsing_res == 1)
		return (print_error(EXPORTERROR1), -1);
	if (parsing_res == 2)
		return (print_export(info->envp), 1);
	info->envp = add_to_envp(info->envp, find_name(str, info),
			find_var(str, info), info);
	return (1);
}
