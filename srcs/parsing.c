/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:34:27 by cpapot            #+#    #+#             */
/*   Updated: 2023/03/04 18:53:02 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	**lexer(t_info *info)
{
	char	**split;
	t_list	*start;
	t_list	**result;
	int		i;

	start = NULL;
	i = 1;
	split = shell_split(info->prompt_string, &info->parsing);
	if (split == NULL)
		print_error(info, "Memory error");
	if (split[0] != NULL)
		start = ft_lstnew(split[0], &info->parsing);
	printf("%s ", split[0]);
	while (split[i] != NULL)
	{
		printf("%s ", split[i]);
		ft_lstadd_back(&start, ft_lstnew(split[i], &info->parsing));
		i++;
	}
	printf("\n\n");
	result = &start;
	return (result);
}

t_list	*check_redirection(t_list *lst, int index, t_list *tmp, t_info *info)
{
	if (lst && !ft_strncmp(lst->content, ">", ft_strlen(lst->content)))
		lst = out_redirection(tmp, index, info);
	else if (lst && !ft_strncmp(lst->content, "<", ft_strlen(lst->content)))
		lst = in_redirection(tmp, index, info);
	else if (lst && !ft_strncmp(lst->content, ">>", ft_strlen(lst->content)))
		lst = out_double_redirection(tmp, index, info);
	else if (lst && !ft_strncmp(lst->content, "<<", ft_strlen(lst->content)))
		lst = in_double_redirection(tmp, index, info);
	return (lst);
}

t_list	*find_redirection(t_list *lst, t_info *info, int id)
{
	t_list	*tmp;
	int		index;

	tmp = lst;
	while (lst)
	{
		lst = tmp;
		index = 0;
		while (lst && lst->content[0] != '<'
			&& lst->content[0] != '>')
		{
			lst = lst->next;
			index++;
		}
		info->tmp = id;
		lst = check_redirection(lst, index, tmp, info);
	}
	lst = tmp;
	return (lst);
}

t_commands	*parsing(t_info *info)
{
	t_list		**lst;
	t_commands	*result;
	int			i;

	i = 0;
	if (ft_strlen(info->prompt_string) == 0)
		return (NULL);
	//gerer les quotes
	lst = lexer(info);
	result = split_pipe(info, *lst);
	info->final_parse = result;
	while (result[i].command != NULL)
	{
		result[i].command
			= find_redirection(result[i].command, info, i);
		i++;
	}
	return (result);
}
