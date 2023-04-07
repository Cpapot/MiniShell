/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:31:14 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/07 17:53:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**add_to_envp(char **envp, char *name, char *var, t_info *info)
{
	int		i;
	char	**result;
	char	*tmp;

	i = 0;
	while (envp[i])
		i++;
	result = stock_malloc(sizeof(char *) * (i + 2), &info->envp_mem);
	if (result == NULL)
		ft_error(ERROR99, info);
	i = -1;
	while (envp[++i])
		result[i] = envp[i];
	if (var == NULL)
	{
		result[i] = name;
		result[i + 1] = NULL;
		return (result);
	}
	tmp = ft_strjoin(name, "=", &info->envp_mem);
	result[i] = ft_strjoin(tmp, var, &info->envp_mem);
	if (result[i] == NULL)
		ft_error(ERROR99, info);
	result[i + 1] = NULL;
	return (result);
}

static char	**modify_envp(int pos, char *var, char *str, t_info *info)
{
	int		i;
	char	**result;

	i = 0;
	result = info->envp;
	if (var == NULL)
		return (result);
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i + 1] == '=')
	{
		if (result[pos][i] != '=')
			result[pos] = ft_strjoin(info->envp[pos], "=", &info->exec_mem);
		result[pos] = ft_strjoin(result[pos], var, &info->envp_mem);
		if (result[pos] == NULL)
			ft_error(ERROR99, info);
	}
	else
	{
		result[pos] = ft_strjoin(ft_stsubstr(str, 0, i + 1, &info->exec_mem),
				var, &info->envp_mem);
		if (result[pos] == NULL)
			ft_error(ERROR99, info);
	}
	return (result);
}

static int	export_parsing(char *str, t_list *lst)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == '+'
		|| (str[0] <= '9' && str[0] >= '0'))
		return (1);
	if (str == NULL || ft_strcmp(str, ""))
		return (2);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (is_char_in_str(str[i], INV_ID_EXPORT))
			return (1);
		i++;
	}
	if ((str[i] == '+' && str[i + 1] != '=') || ((str[i] != '='
				&& str[i] != '+') && lst->next != NULL))
		return (1);
	return (0);
}

int	is_var_already_exist(char *name, char **envp, t_info *info)
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

int	bi_export(t_list *lst, t_info *info)
{
	int		parsing_res;
	int		var_pos;
	char	*str;
	char	*var;

	set_exitstatus(0);
	if (lst == NULL)
		return (print_export(info->envp, info), 1);
	str = lst->content;
	parsing_res = export_parsing(str, lst);
	if (parsing_res == 1)
		return (ft_error(EXPORTERROR1, info), -1);
	if (parsing_res == 2)
		return (print_export(info->envp, info), 1);
	var_pos = is_var_already_exist(find_name(str, info), info->envp, info);
	var = find_var(str, info);
	if (var_pos < 0)
		info->envp = add_to_envp(info->envp, find_name(str, info),
				var, info);
	else if (var_pos >= 0)
		info->envp = modify_envp(var_pos, var, str, info);
	return (1);
}
