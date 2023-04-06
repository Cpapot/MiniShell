/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:31:14 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/06 14:33:20 by cpapot           ###   ########.fr       */
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
		ft_error(ERROR99, info);
	i = 0;
	while (envp[i])
	{
		result[i] = envp[i];
		i++;
	}
	result[i] = ft_strjoin(name, "=", &info->envp_mem);
	if (result[i] == NULL)
		ft_error(ERROR99, info);
	result[i] = ft_strjoin(name, var, &info->envp_mem);
	if (result[i] == NULL)
		ft_error(ERROR99, info);
	result[i + 1] = NULL;
	return (result);
}

static char **modify_envp(int pos, char *var, char *str, t_info *info)
{
	int		i;
	char	**result;

	i = 0;
	result = info->envp;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i + 1] == '=')
	{
		result[pos] = ft_strjoin(info->envp[pos], var, &info->envp_mem);
		if (result[pos] == NULL)
			ft_error(ERROR99, info);
	}
	else
	{
		result[pos] = ft_strjoin(ft_stsubstr(str, 0, i, &info->exec_mem), var
			, &info->envp_mem);
		if (result[pos] == NULL)
			ft_error(ERROR99, info);
	}
	return (result);
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
	if (str[i] == 0)
	{
		result = ft_strdup("", &info->exec_mem);
		if (result == NULL)
			ft_error(ERROR99, info);
		return (result);
	}
	u = i;
	while (str[i] && str[i] != '$')
		i++;
	result = ft_stsubstr(str, u, i, &info->exec_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	return (result);
}

static int	export_parsing(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || ft_strcmp(str, ""))
		return (2);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (is_char_in_str(str[i], INV_ID_EXPORT))
			return (1);
		i++;
	}
	return (0);
}

static int		is_var_already_exist(char *name, char **envp, t_info *info)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(name, find_name(envp[i], info)))
			return (i);
		i++;
	}
	return (-1);
}

int		bi_export(char *str, t_info *info)
{
	int	parsing_res;
	int	var_pos;

	parsing_res = export_parsing(str);
	if (parsing_res == 1)
		return (ft_error(EXPORTERROR1, info), -1);
	if (parsing_res == 2)
		return (print_export(info->envp), 1);
	var_pos = is_var_already_exist(find_name(str, info), info->envp, info);
	if (var_pos == 0)
		info->envp = add_to_envp(info->envp, find_name(str, info),
				find_var(str, info), info);
	else if(var_pos >= 0)
		info->envp = modify_envp(var_pos, find_var(str, info), str, info);
	return (1);
}
