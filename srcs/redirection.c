/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:28 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/28 17:42:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
	met fd.stdout au bon fd et supprimme la redirection et le nom du fichier de la liste
	(aucun free tout sera free avec stock_free)
*/
t_fd	out_redirection(t_list	**lst)
{
	t_list	*tmp;
	t_fd	fd;
	int		i;

	tmp = *lst;
	i = 0;
	while (tmp && tmp->content[0] != '<'
		&& tmp->content[0] != '>')
	{
		tmp = tmp->next;
		i++;
	}
	fd.stdout = open(tmp->next->content, O_RDWR);
	tmp = *lst;
	while (0 != i--)
		tmp = tmp->next;
	ft_printf("%s\n", tmp->content);
	exit(1);
	return (fd);
}
