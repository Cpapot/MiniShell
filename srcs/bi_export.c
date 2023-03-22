/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:31:14 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/22 15:39:59 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#define EXPORTERROR1	"\e[31m\e[1mexport\e[0m: not a valid identifier"

static char	**add_to_envp(char **envp, char *name, char *var, t_info *info)
{
	int		i;
	char	*tmp;
	char	**result;

	i = 0;
	while (envp[i])
		i++;
	result = stock_malloc(sizeof(char *) * (i + 2), &info->envp_mem);
	if (result == NULL)
		print_error_exit(info, ERROR99);
	i = 0;
	while (envp[i])
	{
		result[i] = envp[i];
		i++;
	}
	tmp = ft_strjoin(name, "=", &info->envp_mem);
	result[i] = ft_strjoin(tmp, var, &info->envp_mem);
	if (result[i] == NULL)
		print_error_exit(info, ERROR99);
	result[i + 1] = NULL;
	return (result);

}

static void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

static int	export_parsing(char *str, t_info *info)
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
}

int	export(char *str, t_info *info)
{
	int	parsing_res;

	parsing_res = export_parsing(str);
	if (parsing_res == 0)
		return (0);
	if (parsing_res == 1)
		return (print_error(EXPORTERROR1), 0);
	if (parsing_res == 2)
		return (print_env(info->envp), 1);
	//ajouter fonction qui renvoie name et var
	info->envp = add_to_envp(info->envp, info);
}
