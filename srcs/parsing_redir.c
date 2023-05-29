/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:47:35 by cpapot            #+#    #+#             */
/*   Updated: 2023/05/29 12:21:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redirection(char *str)
{
	if (ft_strcmp(str, "<"))
		return (1);
	else if (ft_strcmp(str, "<<"))
		return (1);
	else if (ft_strcmp(str, ">"))
		return (1);
	else if (ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

static char	*swap_redir_env(char *str, t_info *info)
{
	int		i;
	char	**envp;

	i = 0;
	envp = info->envp;
	while (str && str[i])
	{
		if (str[i] == '\'')
			i += quote_size_env(&str[i], 0);
		else if (str[i] == '$')
		{
			if (is_contain_env(&str[i]) == 1)
				str = swap_envstr(str, info, envp, &i);
			else if (is_contain_env(&str[i]) == 2)
				str = swap_exit(str, info, &i);
		}
		i++;
	}
	return (str);
}

static t_list	*go_next_redirection(t_list *lst)
{
	while (lst->next && !is_redirection(lst->next->content))
		lst = lst->next;
	return (lst);
}

/*
 *This function takes in a linked list lst of parsed command arguments,
 *along with a pointer to a t_info struct and an integer id. It searches and
 *delete for any redirection tokens (e.g. <, >) within lst and creates a new
 *linked list dir of t_dir nodes, where each node represents a redirection and
 *contains the relevant input/output filepaths.
*/
t_list	*find_redirection(t_list *lst, t_info *info, int id)
{
	t_dir	*dir;
	t_list	*tmp;

	tmp = lst;
	dir = ft_lstdirnew(NULL, NULL, &info->final_memparse);
	if (is_redirection(lst->content))
	{
		ft_lstdiradd_back(&dir, ft_lstdirnew(lst->content,
				swap_redir_env(lst->next->content, info), &info->final_memparse));
		tmp = lst->next->next;
	}
	while (lst)
	{
		lst = go_next_redirection(lst);
		if (lst->next && is_redirection(lst->next->content))
		{
			ft_lstdiradd_back(&dir, ft_lstdirnew(lst->next->content,
				swap_redir_env(lst->next->next->content, info), &info->final_memparse));
			lst->next = lst->next->next->next;
		}
		else
			lst = lst->next;
	}
	info->final_parse[id].dir = dir->next;
	return (tmp);
}
