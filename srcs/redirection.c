/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:28 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/04 00:51:38 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*read_input(char *str, t_info *info)
{
	char	*result;
	char	*tmp;

	tmp = stock_malloc(1, &info->parsing);
	if (tmp == NULL)
		print_error(info, "memory error");
	tmp[0] = 0;
	while (42)
	{
		result = readline(BLACK">"WHITE);
		if (ft_strncmp(result, str, ft_strlen(result)) == 0
			&& ft_strlen(result) == ft_strlen(str))
			break ;
		tmp = ft_strjoin(tmp, result, &info->parsing);
		tmp = ft_strjoin(tmp, NL, &info->parsing);
	}
	result = tmp;
	return (result);
}

t_list	*in_double_redirection(t_list	*lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next)
		tmp->next->content = read_input(tmp->next->content, info);
	result->next = tmp->next;
	return (result);
}

t_list	*out_double_redirection(t_list	*lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		info->final_parse[info->tmp].fd.stdout = -1;
	else
		info->final_parse[info->tmp].fd.stdout
			= open(tmp->next->content, O_CREAT | O_RDWR | O_APPEND);
	result->next = tmp->next->next;
	return (result);
}

t_list	*out_redirection(t_list	*lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		info->final_parse[info->tmp].fd.stdout = -1;
	else
		info->final_parse[info->tmp].fd.stdout
			= open(tmp->next->content, O_CREAT | O_RDWR);
	result->next = tmp->next->next;
	return (result);
}

t_list	*in_redirection(t_list *lst, int index, t_info *info)
{
	t_list	*tmp;
	t_list	*result;
	int		i;

	i = 0;
	tmp = lst;
	while (i + 1 <= index)
	{
		i++;
		if (!(i + 1 <= index))
			result = tmp;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		info->final_parse[info->tmp].fd.stdin = -1;
	else
		info->final_parse[info->tmp].fd.stdin
			= open(tmp->next->content, O_RDONLY);
	result->next = tmp->next->next;
	return (result);
}
